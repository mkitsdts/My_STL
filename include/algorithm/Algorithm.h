#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace STL
{
	class Algorithm
	{
	public:
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
			auto size = end - begin;
			if(size < 10)
			{
				shell_sort(begin, end, compare);
			}
			else if(size < 100)
			{
				quick_sort(begin, end, compare);
			}
			else
			{
				merge_sort(begin, end, compare);
			}
		}
		template <typename RandomAccessIterator>
		static void sort(RandomAccessIterator begin, RandomAccessIterator end)
		{
			sort(begin, end, [](*begin, *end) { return *begin < *end; });
		}
	private:
		template <typename RandomAccessIterator>
		static void quick_sort(RandomAccessIterator& begin, RandomAccessIterator& end, bool (*compare)(const value_type&, const value_type&))
		{
			if (begin >= end)
				return;
			RandomAccessIterator base = begin;
			RandomAccessIterator left = begin + 1;
			RandomAccessIterator right = end;
			while(left < right)
			{
				if(left < right)
				{
					if(!compare(*left, *base))
					{
						swap(*left, *right);
						--right;
					}
					else
					{
						if(compare(*right, *base))
						{
							swap(*left, *right);
							++left;
						}
					}
				}
			}
			swap(*base, *right);
			quick_sort(begin, right, compare);
			quick_sort(right + 1, end, compare);
		}

		template <typename RandomAccessIterator>
		static void merge_sort(RandomAccessIterator& begin, RandomAccessIterator& end, bool (*compare)(const value_type&, const value_type&))
		{
			auto merge = [&](RandomAccessIterator& begin1, RandomAccessIterator& end1, RandomAccessIterator& begin2, RandomAccessIterator& end2,
							RandomAccessIterator target, bool (*compare)(const value_type&, const value_type&))
			{
				auto iter1 = begin1;
				auto iter2 = begin2;
				while(iter1 < end1 || iter2 < end2)
				{
					if(iter1 >= end1)
					{
						*target = *iter2;
						++iter2;
						++target;
						continue;
					}
					else if(iter2 >= end2)
					{
						*target = *iter1;
						++iter1;
						++target;
						continue;
					}
					if(compare(*iter1, *iter2))
					{
						*target = *iter1;
						++iter1;
					}
					else
					{
						*target = *iter2;
						++iter2;
					}
					++target;
				}
			};
			if(begin >= end)
				return;
			auto mid = (end - begin) / 2;
			auto target = new value_type[end - begin];
			merge_sort(begin, begin + mid, compare);
			merge_sort(begin + mid + 1, end, compare);
			merge(begin, begin + mid, begin + mid + 1, end, target, compare);
		}

		template <typename RandomAccessIterator>
		static void shell_sort(RandomAccessIterator& begin, RandomAccessIterator& end, bool (*compare)(const value_type&, const value_type&))
		{
			auto size = end - begin;
			auto gap = (size + 1) / 2;
			int i = 0;
			int j = gap;
			while(gap > 0)
			{
				while(j < size)
				{
					if(!compare(*(begin + i), *(begin + j)))
					{
						swap(*(begin + i), *(begin + j));
					}
					++i;
					++j;
				}
				--gap;
			}
		}
	};
}

#endif // !ALGORITHM_H