#ifndef MY_STL_MY_EASY_UNORDERED_SET
#define MY_STL_MY_EASY_UNORDERED_SET
#include "../allocator/Allocator.h"

/*
简单实现标准库实现难度过高
只能插入标准数据类型，且无迭代器
*/

namespace STL
{

	template<class value_type, class alloc = Allocator<value_type>>
	class My_Easy_Unordered_Set
	{
		constexpr auto DEFAULT_BUCKET_COUNT = 10;
	public:
		struct node
		{
			value_type data;
			node* next;
		};
	public:
		My_Easy_Unordered_Set() :_table(nullptr)
		{
		}
		~My_Easy_Unordered_Set()
		{
		}
		void insert(value& val)
		{

		}
		void insert(value&& val)
		{

		}
		void insert(const value& val)
		{

		}

		void erase(value& val)
		{

		}
		void erase(value&& val)
		{

		}
		void erase(const value& val)
		{

		}

		bool empty()
		{

		}

	private:
		

	private:
		node** _table;
	};
}

#endif // !MY_STL_MY_EASY_UNORDERED_SET
