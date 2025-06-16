#pragma once

#include "allocator/allocator.h"
#include <stdexcept>

namespace STL {
constexpr auto REDUNDANCY_TIMES = 1.6;
constexpr auto BEGIN_SIZE_TIMES = 0.3;
constexpr auto ADJUST_TIMES = 1.5;
constexpr auto SEM_SIZE = 20;

template <class T> class My_Deque_Iterator {
public:
  using iterator = My_Deque_Iterator<T>;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

public:
  My_Deque_Iterator() {}
  My_Deque_Iterator(pointer curr, pointer begin, pointer *map)
      : _curr(curr), _map(map), _begin(begin) {}
  My_Deque_Iterator operator=(My_Deque_Iterator &iterator) {
    _curr = iterator._curr;
    _map = iterator._map;
    _begin = iterator._begin;
    return *this;
  }
  My_Deque_Iterator operator++() {
    My_Deque_Iterator tmp = *this;
    if (_curr == _begin + SEM_SIZE) {
    }
  }
  My_Deque_Iterator operator++(int) { return *this; }
  My_Deque_Iterator operator--() {
    My_Deque_Iterator tmp = *this;
    return tmp;
  }
  My_Deque_Iterator operator--(int) { return *this; }
  value_type operator*() {}
  pointer operator->() {}
  pointer _curr;
  pointer _begin;
  pointer *_map;
};

// Deque
template <typename T> class My_Deque {
public:
  using iterator = My_Deque_Iterator<T>;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

public:
  My_Deque()
      : map(nullptr), _begin_index(0), _end_index(0), _size(0), _capacity(0) {}
  My_Deque(int size)
      : _size(size), _begin_index((size >> 1) - 1), _end_index(size >> 1),
        _capacity(size) {
    int seg_count = size / SEM_SIZE;
    map = Allocator<value_type *>::allocate(seg_count);
    _begin_index = size / 2;
    _end_index = size / 2;
    for (int i = 0; i < seg_count; ++i) {
      map[i] = Allocator<value_type>::allocate(SEM_SIZE);
      for (int j = 0; j < SEM_SIZE; ++j) {
        *(map[i] + j) = value_type{};
      }
    }
  }
  My_Deque(std::size_t size, const value_type &value)
      : _size(size), _begin_index(0), _end_index(0), _capacity(size) {
    int seg_count = size / SEM_SIZE;
    map = Allocator<value_type *>::allocate(seg_count);
    _begin_index = size / 2;
    _end_index = size / 2;
    for (int i = 0; i < seg_count; ++i) {
      map[i] = Allocator<value_type>::allocate(SEM_SIZE);
      for (int j = 0; j < SEM_SIZE; ++j) {
        *(map[i] + j) = value;
      }
    }
  }
  My_Deque(const My_Deque &deque)
      : _size(deque._size), _begin_index(deque._begin_index),
        _end_index(deque._end_index), _capacity(deque._capacity) {
    map = Allocator<value_type *>::allocate(deque._size);
    for (int i = 0; i < deque._size; ++i) {
      map[i] = Allocator<value_type>::allocate(SEM_SIZE);
      for (int j = 0; j < SEM_SIZE; ++j) {
        *(map[i] + j) = *(deque.map[i] + j);
      }
    }
  }
  ~My_Deque() {}
  My_Deque operator=(const My_Deque &deque) {
    if (this != &deque) {
      Allocator<value_type *>::dealloc(map, _size);
      _size = deque._size;
      _begin_index = deque._begin_index;
      _end_index = deque._end_index;
      map = deque.map;
      _capacity = deque._capacity;
    }
    return *this;
  }
  // api
public:
  void push_back(const value_type &value) {
    if (_end_index == _capacity || _end_index == _begin_index ||
        _capacity <= 0) {
      adjust();
    }
  }
  void push_front(const value_type &value) {}

  void pop_back() {}
  void pop_front() {}

  value_type front() {
    if (_size == 0 || _begin_index == _end_index) {
      throw std::out_of_range("Deque is empty");
    }
    int block_index = _begin_index / SEM_SIZE;
    int offset = _begin_index % SEM_SIZE;
    return *(map[block_index] + offset);
  }
  value_type back() {
    if (_size == 0 || _begin_index == _end_index) {
      throw std::out_of_range("Deque is empty");
    }
    int block_index = _end_index / SEM_SIZE;
    int offset = _end_index % SEM_SIZE;
    return *(map[block_index] + offset);
  }

  void emplace(iterator &pos, const value_type &value) {
    if (_size >= _capacity || _begin_index == _end_index) {
      adjust();
    }
  }

  iterator begin() { return iterator(_begin_index); }
  iterator end() { return iterator(_end_index + 1); }

  void resize(size_t size) {}

  void clear() {}

  void erase(iterator &pos) {}

  bool empty() { return (_size == 0); }

  size_t size() { return _size; }

  size_t _size;
  value_type **map;
  int _begin_index;
  int _end_index;
  std::size_t _capacity;

private:
  void fillData(value_type &value) const {
    for (size_t i = 0; i < _size; i++) {
    }
  }

  void adjust() const {}
};
} // namespace STL