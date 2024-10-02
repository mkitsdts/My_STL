#ifndef MY_STL_HASHTABLE_H
#define MY_STL_HASHTABLE_H

#include "../allocator/Allocator.h"
#include <string_view>
#include <string>

namespace STL
{
	template<class key, class value_type, class alloc = Allocator<value_type>>
	class HashTable
	{
	public:
		struct node
		{
			value_type data;
			node* next;
			node() :data(value_type()), next(nullptr)
			{
			}
		};
		constexpt auto MAX_BUCKET_COUNT = 16;
		constexpt auto MAX_BUCKET_SIZE = 4;
		HashTable()
		{

		}

		int index(std::string_view )
		{
			
		}

	private:
		node* buckets[MAX_BUCKET_COUNT];
	};
}
#endif // !MY_STL_HASHTABLE_H
