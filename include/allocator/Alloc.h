//
// Created by mkitsdts on 16/6/2024.
//

#ifndef MY_STL_ALLOC_H
#define MY_STL_ALLOC_H
#include <new>
#include <cassert>

namespace STL
{
	class Alloc
	{
	 private:
		//自由链表存储范围内，每一小块区域的内存大小
		enum{ALIGN = 8};
		//自由链表存储范围上限,超过上限则直接operator new分配
		enum{MAX_BYTES = 128};
		//_MAX_BYTES / _ALIGN 表示自由链表存储的区块个数
		enum{NFREELIST = 16};
		//每次希望增加的节点数
		enum{NOBJS = 20};
	 private:
		//自由链表的节点结构，非常细节，节省了一半的空间
		union obj
		{
			union obj* free_list_link;					//指向下一个节点的指针，说明内存管理权还在自己手上，还没有被分配
			char client_data[1];						//client_data的值以后不会用到，这只是表示内存已被分配，该节点无用啦
		};
		//其实这并不是链表，是一个指针数组
		//里面的每一个元素都是一个链表的头指针
		//管理16个链表，每个链表管理不同大小的内存块
		static obj* free_list[NFREELIST];
		
	 private:
		//自建内存池
		static inline char* start_free;                     //内存池起始位置
		static inline char* end_free;                       //内存池结束位置
		static inline size_t heap_size;						//内存池大小

	 private:
		//将 bytes 向上取整
		static size_t ROUND_UP(size_t size)
		{
			//这是标准库写法，非常快（自己写不出来）
			return (size + ALIGN - 1) & ~(ALIGN - 1);
		}

		//根据区块大小，决定使用第n号free_list。 n 从 0 算起
		static size_t FREELIST_INDEX(size_t size)
		{
			return (((size) + ALIGN - 1) / ALIGN - 1);
		}

		//填充free_list
		//返回一个大小为size的对象，并加入大小为n的其他区块到free_list
		static void* refill(size_t size)
		{
			//希望增加的节点数
			size_t nobjs = NOBJS;
			//从内存池里取
			void* chunk = chunk_alloc(size, nobjs);
			
			if (nobjs == 1)
			{
				//取出的空间只够一个对象使用
				return chunk;
			}
			else
			{
				obj** add_needed_free_list = free_list + FREELIST_INDEX(size);
				obj* result = (obj *)(chunk);
				obj* current_obj = nullptr;
				obj* next_obj = nullptr;
				
				*add_needed_free_list = (obj *)((obj *)chunk + size);
				next_obj = (obj *)((obj *)chunk + size);
				//将取出的多余的空间加入到相应的free list里面去
				for (int i = 1;; ++i)
				{
					current_obj = next_obj;
					next_obj = (obj *)((char *)next_obj + size);
					if (nobjs - 1 == i)
					{
						current_obj->free_list_link = nullptr;
						break;
					}
					else
					{
						current_obj->free_list_link = next_obj;
					}
				}
				return result;
			}
		}

		//内存池分配内存的函数
		//配置一大块空间，可容纳nobjs个大小为size的区块
		static char* chunk_alloc(size_t size, size_t& nobjs)
		{
			char* result = nullptr;
			size_t total = size * nobjs;					//需要分配的总空间
			size_t bytes_left = end_free - start_free;		//内存池剩余空间
			
			if (bytes_left >= total)
			{
				//内存池剩余空间满足需要
				result = start_free;
				start_free = start_free + total;
				return result;
			}
			else if (bytes_left >= size)
			{
				//内存池剩余空间不能完全满足需要，但又大于一个区块
				//这里会修改nobjs的值，使其变为内存池剩余空间能够分配的区块数
				nobjs = bytes_left / size;
				total = nobjs * size;
				result = start_free;
				start_free = start_free + total;
				return result;
			}
			else
			{
				//内存池剩余空间不足一个区块的大小
				size_t need_bytes = 2 * total + ROUND_UP(heap_size >> 4);
				if (bytes_left > 0)
				{
					//内存池还有一些零头，先配给适当的free_list
					//最终结果是，内存池起始位置变为链表首节点
					obj** appropriate_free_list = free_list + FREELIST_INDEX(bytes_left);
					((obj*)start_free)->free_list_link = *appropriate_free_list;
					*appropriate_free_list = (obj*)(start_free);
					//有点复杂，不好理解
				}
				//尝试申请内存
				start_free = static_cast<char*>(operator new(need_bytes));
				//内存池申请失败
				if (start_free == nullptr)
				{
					//将内存池里的内存全部分配到free_list
					obj** temp_free_list = nullptr;
					obj* temp = nullptr;
					for (int i = 0; i < NFREELIST; ++i)
					{
						temp_free_list = free_list + i;
						temp = *temp_free_list;
						if (temp != nullptr)
						{
							*temp_free_list = temp->free_list_link;
							start_free = (char *)temp;
							end_free = start_free + ALIGN * i;
							return chunk_alloc(size, nobjs);
						}
					}
					end_free = nullptr;
				}
				//内存池申请成功
				//递归调用自己，确保内存池有足够的空间
				heap_size += need_bytes;
				end_free = start_free + need_bytes;
				return chunk_alloc(size, nobjs);
			}
		}

	 public:
		//分配内存
		static void* allocate(size_t size)
		{
			//申请size个字节的内存
			//如果大于申请的内存128字节，直接向系统申请
			if (size > MAX_BYTES)
			{
				return operator new(size);
			}
			//index为合适的free_list节点
			size_t index = FREELIST_INDEX(size);
			obj* list = free_list[index];
			if (list)
			{
				//此list还有空间给我们
				free_list[index] = list->free_list_link;
				return list;
			}
			else
			{
				//此list没有足够的空间，需要从内存池里面取空间
				return refill(ROUND_UP(size));
			}
		}
		//释放内存
		static void deallocate(void* ptr, size_t bytes)
		{
			if (bytes > MAX_BYTES)
			{
				operator delete(ptr);
			}
			else
			{
				size_t index = FREELIST_INDEX(bytes);
				obj *node = static_cast<obj *>(ptr);
				node->free_list_link = free_list[index];
				free_list[index] = node;
			}
		}
		//重新分配内存
		static void* reallocate(void* ptr, size_t old_sz, size_t new_sz)
		{
			deallocate(ptr, old_sz);
			ptr = allocate(new_sz);
			return ptr;
		}

	 public:
		Alloc()
		{
			start_free = nullptr;
			end_free = nullptr;
			heap_size = 0;
		};
		~Alloc() = default;
	};
	char* start_free = nullptr;
	char* end_free = nullptr;
	size_t heap_size = 0;
	Alloc::obj* Alloc::free_list[NFREELIST] = { nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr };
}
#endif //MY_STL_ALLOC_H
