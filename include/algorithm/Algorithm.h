#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "./iterator/iterator.hpp"
namespace STL
{
	struct Algorithm
	{
		template <typename value_type>
		static void swap(value_type& a, value_type& b)
		{
			value_type tmp = a;
			a = b;
			b = tmp;
		}

		template <typename RandomAccessIterator>
		static void sort(RandomAccessIterator& begin, RandomAccessIterator& end, bool (*compare)(const value_type&, const value_type&))
		{
			
		}
		template <typename RandomAccessIterator>
		static void sort(RandomAccessIterator& begin, RandomAccessIterator& end)
		{
			sort(begin, end, [](*begin, *end) { return *begin < *end; });
		}
	};
}

#endif // !ALGORITHM_H