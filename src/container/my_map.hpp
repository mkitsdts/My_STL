#pragma once
#include "base/pair.hpp"
#include "container/my_set.hpp"

namespace STL {
template <class Key, class T, class Compare = std::less<Key>> class My_Map {
public:
  My_Map() = default;
  ~My_Map() = default;
  My_Map(const My_Map &other) : tree(other.tree) {}
  My_Map(My_Map &&other) noexcept : tree(std::move(other.tree)) {}
  My_Map &operator=(const My_Map &other) {
    tree = other.tree;
    return *this;
  }
  My_Map &operator=(My_Map &&other) noexcept {
    tree = std::move(other.tree);
    return *this;
  }
  T operator[](const Key &key) {
    auto it = tree.find(pair<Key, T>(key, T()));
    if (it != tree.end()) {
      return (*it).second;
    } else {
      tree.insert(pair<Key, T>(key, T()));
      it = tree.find(pair<Key, T>(key, T()));
      return (*it).second;
    }
  }
  void insert(const pair<Key, T> &value) { tree.insert(value); }
  void insert(Key key, T value) { tree.insert(pair<Key, T>(key, value)); }
  void erase(const Key &key) { tree.erase(pair<Key, T>(key, T())); }
  void clear() { tree.clear(); }
  int count(const Key &key) { return tree.find(pair<Key, T>(key, T())); }
  std::size_t size() { return tree.size(); }
  bool empty() { return tree.empty(); }
  auto begin() { return tree.begin(); }
  auto end() { return tree.end(); }

private:
  My_Set<pair<Key, T>, Compare, Alloc> tree;
};
} // namespace STL
