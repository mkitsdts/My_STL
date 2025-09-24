//
// Created by mkitsdts on 16/6/2024.
//

#pragma once
#include "allocator/alloc.hpp"

namespace STL {
template <typename T> class Allocator {
public:
  using value_type = T;
  Allocator() = default;
  ~Allocator() = default;

  // allocate one value_type
  static value_type *allocate() {
    return static_cast<value_type *>(
        Alloc::allocate((std::size_t)sizeof(value_type)));
  }
  // allocate n value_type
  static value_type *allocate(const std::size_t &n) {
    if (n <= 0) {
      return nullptr;
    } else {
      return static_cast<value_type *>(
          Alloc::allocate(n * (std::size_t)sizeof(value_type)));
    }
  }

  // deallocate n value_type memory
  static void deallocate(value_type *ptr, std::size_t n) {
    Alloc::deallocate(static_cast<void *>(ptr), n);
  }

  // default construct
  static void construct(value_type *ptr) { new (ptr) value_type{}; }
  static void construct(value_type *ptr, const value_type &value) {
    new (ptr) value_type{value};
  }

  static void destroy(value_type *ptr) { ptr->~value_type(); }
  static void destroy(value_type *begin, value_type *end) {
    while (begin != end) {
      begin->~value_type();
      ++begin;
    }
  }
};
} // namespace STL
