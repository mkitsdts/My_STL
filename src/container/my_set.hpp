#pragma once
#include "allocator/allocator.hpp"
#include "base/rbtree.hpp"
#include <functional>

namespace STL {
template <class Key, class Compare = std::less<Key>,
          class Alloc = Allocator<Key>>
class My_Set {
public:
  using value_type = Key;

public:
  void insert(value_type &value) { tree.insert(value); }
  void insert(const value_type &value) { tree.insert(value); }
  void erase(value_type &value) { tree.erase(value); }
  void erase(const value_type &value) { tree.erase(value); }
  void clear() { tree.clear(); }
  std::size_t size() { return tree.size(); }
  bool empty() { return tree.empty(); }
  bool find(value_type &value) { return tree.find(value); }
  bool find(const value_type &value) { return tree.find(value); }
  auto begin() { return tree.begin(); }
  auto end() { return tree.end(); }

private:
  RBTree<Key> tree;
};
} // namespace STL