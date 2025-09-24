#pragma once

#include "allocator/allocator.hpp"
#include "container/my_vector.hpp"
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

private:
  template <class value_type> struct segment {
    segment() : begin(0), end(0), data(0), next(nullptr), prev(nullptr) {}
    My_Vector<value_type> data;
    segment *next;
    segment *prev;
    int begin;
    int end;
  };

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
    if (_size >= _capacity) {
      adjust();
    }
    int block_index = _end_index / SEM_SIZE;
    int offset = _end_index % SEM_SIZE;
    *(map[block_index] + offset) = value;
    ++_end_index;
    ++_size;
  }
  void push_front(const value_type &value) {
    if (_size >= _capacity) {
      adjust();
    }
    --_begin_index;
    int block_index = _begin_index / SEM_SIZE;
    int offset = _begin_index % SEM_SIZE;
    *(map[block_index] + offset) = value;
    ++_size;
  }

  void pop_back() {
    if (_size == 0 || _begin_index == _end_index) {
      throw std::out_of_range("Deque is empty");
    }
    --_end_index;
    --_size;
  }
  void pop_front() {
    if (_size == 0 || _begin_index == _end_index) {
      throw std::out_of_range("Deque is empty");
    }
    ++_begin_index;
    --_size;
  }

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
    int index = (pos._curr - pos._begin) + _begin_index;
    for (int i = _end_index; i > index; --i) {
      int curr_block_index = i / SEM_SIZE;
      int curr_offset = i % SEM_SIZE;
      int prev_block_index = (i - 1) / SEM_SIZE;
      int prev_offset = (i - 1) % SEM_SIZE;
      *(map[curr_block_index] + curr_offset) =
          *(map[prev_block_index] + prev_offset);
    }
  }

  iterator begin() { return iterator(_begin_index); }
  iterator end() { return iterator(_end_index + 1); }

  void resize(std::size_t size) {
    if (size <= 0) {
      throw std::out_of_range("Size must be greater than 0");
    }
    if (size > _capacity) {
      adjust();
    }
    _size = size;
    _begin_index = (_capacity - size) / 2;
    _end_index = _begin_index + size;
  }

  void clear() {
    _begin_index = _capacity / 2;
    _end_index = _capacity / 2;
    _size = 0;
  }

  void erase(iterator &pos) {
    if (_size == 0 || _begin_index == _end_index) {
      throw std::out_of_range("Deque is empty");
    }
    int index = (pos._curr - pos._begin) + _begin_index;
    int block_index = index / SEM_SIZE;
    int offset = index % SEM_SIZE;
    for (int i = index; i < _end_index - 1; ++i) {
      int curr_block_index = i / SEM_SIZE;
      int curr_offset = i % SEM_SIZE;
      int next_block_index = (i + 1) / SEM_SIZE;
      int next_offset = (i + 1) % SEM_SIZE;
      *(map[curr_block_index] + curr_offset) =
          *(map[next_block_index] + next_offset);
    }
  }

  bool empty() { return (_size == 0); }

  std::size_t size() { return _size; }

private:
  void adjust() {
    int new_capacity = _capacity * REDUNDANCY_TIMES;
    int seg_count = new_capacity / SEM_SIZE;
    value_type **new_map = Allocator<value_type *>::allocate(seg_count);
    int new_begin_index = (new_capacity - _size) / 2;
    int new_end_index = new_begin_index + _size;
    for (int i = 0; i < seg_count; ++i) {
      new_map[i] = Allocator<value_type>::allocate(SEM_SIZE);
      for (int j = 0; j < SEM_SIZE; ++j) {
        *(new_map[i] + j) = value_type{};
      }
    }
    int old_index = _begin_index;
    for (int i = new_begin_index; i < new_end_index; ++i, ++old_index) {
      int old_block_index = old_index / SEM_SIZE;
      int old_offset = old_index % SEM_SIZE;
      int new_block_index = i / SEM_SIZE;
      int new_offset = i % SEM_SIZE;
      *(new_map[new_block_index] + new_offset) =
          *(map[old_block_index] + old_offset);
    }
    Allocator<value_type *>::deallocate(map, _capacity / SEM_SIZE);
    map = new_map;
    _begin_index = new_begin_index;
    _end_index = new_end_index;
    _capacity = new_capacity;
  }
  value_type **map;
  int _begin_index;
  int _end_index;
  std::size_t _size;
  std::size_t _capacity;
};
} // namespace STL