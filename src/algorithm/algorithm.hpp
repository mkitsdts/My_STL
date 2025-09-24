#pragma once
#include <functional>

namespace STL {
template <typename value_type>
inline static void swap(value_type &a, value_type &b) {
  value_type tmp = a;
  a = b;
  b = tmp;
}

// too easy, just for test
template <typename RandomAccessIterator, typename Compare>
inline static void sort(RandomAccessIterator begin, RandomAccessIterator end,
                        Compare compare) {
  auto size = end - begin;
  if (size < 10) {
    shell_sort(begin, end, compare);
    // merge_sort(begin, end, compare);
  } else {
    heap_sort(begin, end, compare);
    // quick_sort(begin, end, compare);
  }
}

template <typename RandomAccessIterator>
inline static void sort(RandomAccessIterator begin, RandomAccessIterator end) {
  sort(begin, end, [](RandomAccessIterator begin, RandomAccessIterator end) {
    return *begin < *end;
  });
}

template <typename RandomAccessIterator, typename Compare>
static void quick_sort(RandomAccessIterator begin, RandomAccessIterator end,
                       Compare compare) {
  if (begin >= end) {
    return;
  }
  RandomAccessIterator base = begin;
  RandomAccessIterator left = begin + 1;
  RandomAccessIterator right = end;
  while (left < right) {
    if (left < right) {
      if (!compare(left, base)) {
        swap(*left, *right);
        --right;
      } else {
        if (compare(right, base)) {
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

/*template <class RandomAccessIterator, class Compare>
static void merge_sort(RandomAccessIterator begin, RandomAccessIterator end,
Compare compare)
{
        auto merge = [&](RandomAccessIterator begin1, RandomAccessIterator end1,
        RandomAccessIterator begin2, RandomAccessIterator end2,
                RandomAccessIterator target, Compare comp)
                {
                        auto iter1 = begin1;
                        auto iter2 = begin2;
                        while (iter1 < end1 || iter2 < end2)
                        {
                                if (iter1 >= end1)
                                {
                                        *target = *iter2;
                                        ++iter2;
                                        ++target;
                                        continue;
                                }
                                else if (iter2 >= end2)
                                {
                                        *target = *iter1;
                                        ++iter1;
                                        ++target;
                                        continue;
                                }
                                if (comp(*iter1, *iter2))
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
        if (begin >= end)
                return;
        auto mid = (end - begin) / 2;
        auto target = new value_type[end - begin];
        merge_sort(begin, begin + mid, compare);
        merge_sort(begin + mid + 1, end, compare);
        merge(begin, begin + mid, begin + mid + 1, end, target, compare);
}*/

template <class RandomAccessIterator, class Compare>
inline static void shell_sort(RandomAccessIterator begin,
                              RandomAccessIterator end, Compare compare) {
  auto size = end - begin;
  auto gap = (size + 1) / 2;
  while (gap > 0) {
    for (int i = 0, j = gap; j < size; ++i, ++j) {
      if (!compare((begin + i), (begin + j))) {
        swap(*(begin + i), *(begin + j));
      }
    }
    --gap;
  }
}

template <class RandomAccessIterator, class Compare>
inline static void heap_sort(RandomAccessIterator begin,
                             RandomAccessIterator end, Compare compare) {
  std::function<void(RandomAccessIterator, int, int)> heapify =
      [&](RandomAccessIterator begin, int size, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && compare((begin + left), (begin + largest))) {
          largest = left;
        }
        if (right < size && compare((begin + right), (begin + largest))) {
          largest = right;
        }
        if (largest != i) {
          swap(*(begin + i), *(begin + largest));
          heapify(begin, size, largest);
        }
      };

  auto size = end - begin;
  for (int i = size / 2 - 1; i >= 0; --i) {
    heapify(begin, size, i);
  }
  for (int i = size - 1; i >= 0; --i) {
    swap(*begin, *(begin + i));
    heapify(begin, i, 0);
  }
}

template <class T> inline static int log(T x, T base) {
  if (x <= 0 || base <= 1) {
    return -1; // Invalid input
  }
  int result = 0;
  while (x >= base) {
    x /= base;
    ++result;
  }
  return result;
}
} // namespace STL