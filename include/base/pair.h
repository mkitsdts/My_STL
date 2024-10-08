#ifndef MY_STL_PAIR_H
#define MY_STL_PAIR_H

namespace STL
{
	template<class T1, class T2>
	struct pair
	{
		using first_type = T1;
		using second_type = T2;

		first_type _first;
		first_type _second;

		pair() :_first(first_type()), _second(second_type())
		{
		}
		pair(const first_type& a, const second_type& b) :_first(a), _second(b)
		{
		}
		pair(first_type&& a, second_type&& b) :_first(a), _second(b)
		{
		}
		pair(const pair& p) :_first(p._first), _second(p._second)
		{
		}
		pair& operator=(const pair& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}
		bool operator==(const pair& p)
		{
			return first == p.first && second == p.second;
		}
		bool operator!=(const pair& p)
		{
			return !(*this == p);
		}

		first_type& first()
		{
			return _first;
		}
		const first_type& first() const
		{
			return _first;
		}
		second_type& second()
		{
			return _second;
		}
		const second_type& second() const
		{
			return _second;
		}
	};

	template<class T1, class T2>
	pair<T1,T2> make_pair(T1 first,T2 second)
	{
		return pair<T1, T2>(first, second);
	}
}

#endif // !MY_STL_PAIR_H