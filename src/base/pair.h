#pragma once

namespace STL
{
	template<class T1, class T2>
	struct pair
	{
		using first_type = T1;
		using second_type = T2;

		first_type first;
		first_type second;

		pair() :first(first_type()), second(second_type())
		{
		}
		pair(const first_type& a, const second_type& b) :first(a), second(b)
		{
		}
		pair(first_type&& a, second_type&& b) :first(a), second(b)
		{
		}
		pair(const pair& p) :first(p.first), second(p.second)
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
	};

	template<class T1, class T2>
	pair<T1,T2> make_pair(T1 first,T2 second)
	{
		return pair<T1, T2>(first, second);
	}
}