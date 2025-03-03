#pragma once
#include "base/hashtable.h"

namespace STL
{

	template<class value_type, class alloc = Allocator<value_type>>
	class My_Easy_Unordered_Set
	{
	public:
		My_Easy_Unordered_Set()
		{
		}
		~My_Easy_Unordered_Set()
		{
		}
		void insert(const value& val)
		{
			_table.insert(val);
		}

		void erase(const value& val)
		{
			_table.erase(val);
		}

		int count()
		{
			return _table.count();
		}

	private:
		HashTable<value_type> _table;
	};
}
