/*
mkitsdts
*/
#pragma once
#include "allocator/allocator.h"

namespace STL {
template <class T> struct My_List_Node {
public:
  My_List_Node() : data(T{}), next(nullptr), prev(nullptr) {}
  My_List_Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
  ~My_List_Node() {
    next = nullptr;
    prev = nullptr;
  }

public:
  T &get_data() { return data; }
  void set_data(const T &value) { data = value; }
  My_List_Node *get_next() { return next; }
  void set_next(My_List_Node *node) { next = node; }
  My_List_Node *get_prev() { return prev; }
  void set_prev(My_List_Node *node) { prev = node; }
  void operator=(My_List_Node &node) {
    data = node.data;
    next = node.next;
    prev = node.prev;
  }

private:
  T data;
  My_List_Node *next;
  My_List_Node *prev;
};

template <class T> class My_List_Iterator {
public:
  using value_type = T;
  using pointer = My_List_Node<T> *;
  using reference = My_List_Node<T> &;
  using iterator = My_List_Iterator<T>;

public:
  My_List_Iterator(pointer ptr) noexcept { _ptr = ptr; }
  My_List_Iterator(const My_List_Iterator &it) noexcept { *this = it; }

public:
  iterator operator++() {
    iterator tmp = *this;
    _ptr = _ptr->get_next();
    return tmp;
  }
  iterator operator++(int) { return My_List_Iterator(_ptr->get_next()); }
  iterator operator--() {
    iterator tmp = *this;
    _ptr = _ptr->get_prev();
    return tmp;
  }
  iterator operator--(int) { return My_List_Iterator(_ptr->get_prev()); }
  value_type &operator*() { return (_ptr->get_data()); }
  pointer &operator->() { return _ptr; }
  bool operator==(const iterator &it) { return _ptr == it._ptr; }
  bool operator!=(const iterator &it) { return _ptr != it._ptr; }

private:
  pointer _ptr;
};

template <class T, class alloc = STL::Allocator<T>> class My_List {
public:
  using value_type = T;
  using iterator = My_List_Iterator<T>;
  using reference = T &;
  using const_iterator = const T *;
  using const_reference = const T &;
  using node = My_List_Node<T>;

public:
  My_List() : head(nullptr), tail(nullptr), _size(0) {}
  My_List(const My_List &list) {
    resize(list.size());
    iterator temp = list.head;
    for (size_t i = 0; i < list.size(); ++i) {
      push_back(*temp);
      ++temp;
    }
  }
  ~My_List() { clear(); }

public:
  value_type &front() {
    if (head) {
      return head->get_data();
    }
  }
  value_type &back() {
    if (head != tail) {
      return tail->get_data();
    }
  }
  iterator begin() {
    if (head != tail) {
      return iterator(head);
    }
    return iterator(nullptr);
  }
  iterator end() {
    if (head != tail) {
      return iterator(nullptr);
    }
    return iterator(tail);
  }
  iterator at(size_t pos) {
    if (pos < _size) {
      auto it = head;
      for (size_t i = 0; i < pos; ++i) {
        it = it->get_next();
      }
      return iterator(it);
    }
  }
  void push_back(const_reference value) {
    if (_size == 0) {
      head = new node(value);
      tail = head;
      ++_size;
    } else {
      node *temp = new node(value);
      tail->set_next(temp);
      temp->set_prev(tail);
      tail = temp;
      ++_size;
    }
  }
  void push_back(reference value) {
    if (_size == 0) {
      head = new node(value);
      tail = head;
      ++_size;
    } else {
      node *temp = new node(value);
      tail->set_next(temp);
      temp->set_prev(tail);
      tail = temp;
      ++_size;
    }
  }
  void push_front(const_reference value) {
    if (_size == 0) {
      head = new node(value);
      tail = head;
      ++_size;
    } else {
      node *temp = new node(value);
      head->set_prev(temp);
      temp->set_next(head);
      head = temp;
      ++_size;
    }
  }
  void push_front(value_type value) {
    if (_size == 0) {
      head = new node(value);
      tail = head;
      ++_size;
    } else {
      node *temp = new node(value);
      head->set_prev(temp);
      temp->set_next(head);
      head = temp;
      ++_size;
    }
  }
  void pop_back() {
    if (_size == 0) {
      return;
    } else if (_size == 1) {
      delete tail;
      head = nullptr;
      tail = nullptr;
      --_size;
    } else {
      node *temp = tail;
      tail = tail->get_prev();
      delete temp;
      --_size;
    }
  }
  void pop_front() {
    if (_size == 0) {
      return;
    } else if (_size == 1) {
      delete head;
      head = nullptr;
      tail = nullptr;
      --_size;
    } else {
      node *temp = head;
      head = head->get_next();
      delete temp;
      --_size;
    }
  }
  void clear() {
    while (_size > 0) {
      pop_back();
    }
  }
  iterator erase(const iterator &pos) {
    if (_size <= 0) {
      return nullptr;
    } else if (*pos == head) {
      --_size;
      pop_front();
      return nullptr;
    } else if (*pos == tail) {
      --_size;
      pop_back();
      return tail;
    } else {
      auto temp = pos;
      --pos;
      --_size;
      *pos->set_next(*temp->get_next());
      *temp->get_next()->set_prev(*pos);
      delete temp;
      --_size;
      return pos;
    }
  }
  iterator erase(const iterator &first, const iterator &last) {
    auto temp = first;
    while (first != last) {
      erase(first);
      ++temp;
    }
    --_size;
    return *first->get_prev();
  }
  iterator erase(size_t pos) {
    auto temp = head;
    while (pos--) {
      ++temp;
    }
    --_size;
    return erase(temp);
  }

  size_t size() { return _size; }

private:
  node *head;
  node *tail;
  size_t _size;
};
} // namespace STL
