#pragma once
#include "base/hashtable.hpp"

namespace STL {
template <class value_type, class alloc = Allocator<value_type>>
class My_Easy_Unordered_Set {
public:
  My_Easy_Unordered_Set() {}
  ~My_Easy_Unordered_Set() {}

  void insert(const value_type &val) { _table.insert(val); }

  void erase(const value_type &val) { _table.erase(val); }

  int count() { return _table.count(); }

  std::size_t size() { return _table.size(); }

  bool empty() { return _table.size() == 0; }

  bool find(const value_type &val) { return _table.find(val); }

private:
  HashTable<value_type> _table;
};
} // namespace STL
