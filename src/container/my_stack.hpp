#pragma once
#include "container/my_deque.hpp"

namespace STL {

template <class value_type> class My_Stack {
public:
  My_Stack() = default;
  ~My_Stack() = default;

  void push(const value_type &value) { _deque.push_back(value); }
  void pop() { _deque.pop_front(); }
  value_type top() { return _deque.front(); }
  std::size_t size() { return _deque.size(); }
  bool empty() { return _deque.empty(); }

private:
  My_Deque<value_type> _deque;
};

} // namespace STL