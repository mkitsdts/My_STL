#pragma once

#include "allocator/allocator.hpp"
#include <string>

namespace STL {
constexpr std::size_t MAX_BUCKET_COUNT = 16;
constexpr std::size_t MAX_BUCKET_SIZE = 4;
template <class T, class alloc = Allocator<T>> class HashTable {
public:
  using value_type = T;
  struct node {
    value_type data;
    node *next;
    node() : data(value_type()), next(nullptr) {}
  };
  HashTable() {
    for (int i = 0; i < MAX_BUCKET_COUNT; i++) {
      buckets[i] = nullptr;
    }
  }
  void insert(const value_type &value) {
    std::string key = std::to_string(value);
    int idx = index(key);
    if (buckets[idx] == nullptr) {
      buckets[idx] = new node();
      buckets[idx]->data = value;
    } else {
      node *temp = buckets[idx];
      while (temp->next != nullptr) {
        if (temp->data == value)
          return;
        temp = temp->next;
      }
      temp->next = new node();
      temp->next->data = value;
    }
  }
  void erase(const value_type &value) {
    std::string key = std::to_string(value);
    int idx = index(key);
    if (buckets[idx] == nullptr) {
      return;
    }
    node *temp = buckets[idx];
    if (temp->data == value) {
      buckets[idx] = temp->next;
      delete temp;
      return;
    }
    while (temp->next != nullptr) {
      if (temp->next->data == value) {
        node *del = temp->next;
        temp->next = del->next;
        delete del;
        return;
      }
      temp = temp->next;
    }
  }

  int count(const value_type &value) {
    std::string key = std::to_string(value);
    int idx = index(key);
    if (buckets[idx] == nullptr) {
      return 0;
    }
    node *temp = buckets[idx];
    while (temp != nullptr) {
      if (temp->data == value) {
        return 1;
      }
      temp = temp->next;
    }
    return 0;
  }

private:
  int index(const std::string &str) {
    int hash = 0;
    for (auto &c : str) {
      hash += c;
    }
    return hash % MAX_BUCKET_COUNT;
  }
  node *buckets[MAX_BUCKET_COUNT];
};
} // namespace STL
