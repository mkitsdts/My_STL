#pragma once
#include "container/my_deque.hpp"

namespace STL {
template <typename T> class My_Queue {
public:
  using value_type = T;
  My_Queue() = default;

  void push(const value_type &value) { _deque.push_back(value); }
  void pop() { _deque.pop_front(); }
  value_type front() { return _deque.front(); }
  value_type back() { return _deque.back(); }
  std::size_t size() { return _deque.size(); }
  bool empty() { return _deque.empty(); }

private:
  My_Deque<value_type> _deque;
};
} // namespace STL