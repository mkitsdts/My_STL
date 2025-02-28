//
// Created by mkitsdts on 16/6/2024.
//

#pragma once
#include <new>
#include <cassert>
constexpr auto ALIGN = 8;
constexpr auto MAX_BYTES = 128;
constexpr auto NFREELIST = 16;
constexpr auto NOBJS = 20;

namespace STL
{
	class Alloc
	{
	private:
		union obj
		{
			union obj* free_list_link;
			char client_data[1];
		};
		static obj* free_list[NFREELIST];
		
	private:
		static inline char* start_free;
		static inline char* end_free;
		static inline size_t heap_size;

	private:
		static size_t ROUND_UP(size_t size)
		{
			return (size + ALIGN - 1) & ~(ALIGN - 1);
		}

		static size_t FREELIST_INDEX(size_t size)
		{
			return (((size) + ALIGN - 1) / ALIGN - 1);
		}

		static void* refill(size_t size)
		{
			size_t nobjs = NOBJS;
			void* chunk = chunk_alloc(size, nobjs);
			
			if (nobjs == 1)
			{
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
				//��ȡ���Ķ���Ŀռ���뵽��Ӧ��free list����
				for (size_t i = 1;; ++i)
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

		//�ڴ�ط����ڴ�ĺ���
		//����һ���ռ䣬������nobjs����СΪsize����
		static char* chunk_alloc(size_t size, size_t& nobjs)
		{
			char* result = nullptr;
			size_t total = size * nobjs;					//��Ҫ������ܿ�
			size_t bytes_left = end_free - start_free;		//�ڴ��ʣ���
			
			if (bytes_left >= total)
			{
				//�ڴ��ʣ��ռ�������Ҫ
				result = start_free;
				start_free = start_free + total;
				return result;
			}
			else if (bytes_left >= size)
			{
				//�ڴ��ʣ��ռ䲻����ȫ������Ҫ�����ִ���һ����
				//������޸�nobjs��ֵ��ʹ���Ϊ�ڴ��ʣ��ռ��ܹ����������
				nobjs = bytes_left / size;
				total = nobjs * size;
				result = start_free;
				start_free = start_free + total;
				return result;
			}
			else
			{
				//�ڴ��ʣ��ռ䲻��һ������Ĵ�С
				size_t need_bytes = 2 * total + ROUND_UP(heap_size >> 4);
				if (bytes_left > 0)
				{
					//�ڴ�ػ���һЩ��ͷ��������ʵ���free_list
					//���ս���ǣ��ڴ����ʼλ�ñ�Ϊ�����׽�
					obj** appropriate_free_list = free_list + FREELIST_INDEX(bytes_left);
					((obj*)start_free)->free_list_link = *appropriate_free_list;
					*appropriate_free_list = (obj*)(start_free);
					//�е㸴�ӣ���������
				}
				//���������ڴ�
				start_free = static_cast<char*>(operator new(need_bytes));
				//�ڴ������ʧ
				if (start_free == nullptr)
				{
					//���ڴ������ڴ�ȫ�����䵽free_list
					obj** temp_free_list = nullptr;
					obj* temp = nullptr;
					for (size_t i = 0; i < NFREELIST; ++i)
					{
						temp_free_list = free_list + i;
						temp = *temp_free_list;
						if (temp != nullptr)
						{
							*temp_free_list = temp->free_list_link;
							start_free = (char*)temp;
							end_free = start_free + ALIGN * i;
							return chunk_alloc(size, nobjs);
						}
					}
					end_free = nullptr;
				}
				//�ڴ�������
				//�ݹ�����Լ���ȷ���ڴ�����㹻�Ŀռ�
				heap_size += need_bytes;
				end_free = start_free + need_bytes;
				return chunk_alloc(size, nobjs);
			}
		}

	 public:
		//�����ڴ�
		static void* allocate(size_t size)
		{
			//����size���ֽڵ��ڴ�
			//�������������ڴ�128�ֽڣ�ֱ����ϵͳ����
			if (size > MAX_BYTES)
			{
				return operator new(size);
			}
			//indexΪ���ʵ�free_list�ڵ�
			size_t index = FREELIST_INDEX(size);
			obj* list = free_list[index];
			if (list)
			{
				//��list���пռ��
				free_list[index] = list->free_list_link;
				return list;
			}
			else
			{
				//��listû���㹻�Ŀռ䣬��Ҫ���ڴ������ȡ�ռ�
				return refill(ROUND_UP(size));
			}
		}
		//�ͷ��ڴ�
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
		//���·����ڴ�
		static void* reallocate(void*& ptr, size_t old_sz, size_t new_sz)
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
