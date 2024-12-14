#ifndef MY_STL_MY_EASY_UNORDERED_SET
#define MY_STL_MY_EASY_UNORDERED_SET
#include "../base/hashtable.h"

/*
��ʵ�ֱ�׼��ʵ���Ѷȹ���
ֻ�ܲ����׼�������ͣ����޵�����
*/

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
		void insert(value& val)
		{
			_table.insert(val);
		}
		void insert(value&& val)
		{
			_table.insert(val);
		}
		void insert(const value& val)
		{
			_table.insert(val);
		}

		void erase(value& val)
		{
			_table.erase(val);
		}
		void erase(value&& val)
		{
			_table.erase(val);
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

#endif // !MY_STL_MY_EASY_UNORDERED_SET
