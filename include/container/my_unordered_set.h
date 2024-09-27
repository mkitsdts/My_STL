#ifndef MY_STL_MY_UNORDERED_SET
#define MY_STL_MY_UNORDERED_SET

#include "../allocator/Allocator.h"
#include "unordered_set"
namespace STL
{
	int default_hash(const char* str)
	{
		unsigned int seed = 131;
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}

	template<class key, class value, class hash, class equalkey,class alloc = Allocator<value>>
	class my_unordered_set
	{
		//equalkey判断两个key是否相等
		//hash是一个函数对象，用来计算key的hash值
		//alloc是一个分配器，用来分配内存
		constexpr auto DEFAULT_BUCKET_COUNT = 10;
	public:
		struct node
		{

		};
	public:
		void insert(value& val)
		{

		}
		void insert(value&& val)
		{

		}
		void insert(const value& val)
		{

		}

		bool empty()
		{

		}

	private:
		

	private:
		node* _table;
	};
}

#endif // !MY_STL_MY_UNORDERED_SET
