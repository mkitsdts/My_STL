#include <iostream>

#include "algorithm/algorithm.hpp"
#include "base/hashtable.hpp"
#include "base/rbtree.hpp"
#include "container/my_deque.hpp"
#include "container/my_list.hpp"
#include "container/my_set.hpp"
#include "container/my_string.hpp"
#include "container/my_vector.hpp"
#include <ctime>

using namespace STL;
using std::cout;
using std::endl;

void string_test() {
  My_String str("hello world");
  cout << str << endl;
}

void vector_test() {
  My_Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  cout << vec.size() << endl;
  cout << vec.capacity() << endl;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void list_test() {
  My_List<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(4);
  cout << l.size() << endl;
  int i = 0;
  for (auto it = l.begin(); it != l.end(); ++it) {
    cout << i++ << ": " << *it << endl;
  }
}

void set_test() {
  My_Set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  s.insert(4);
  s.insert(5);
  for (auto iter = s.begin(); iter != s.end(); ++iter) {
    cout << *iter << endl;
  }
}

void rbtree_test() {
  RBTree<int> rbtree;
  cout << "RBTree size: " << rbtree.size() << endl;
  rbtree.insert(1);
  rbtree.insert(2);
  rbtree.insert(3);
  rbtree.insert(4);
  rbtree.insert(5);
  rbtree.insert(6);

  cout << "RBTree size: " << rbtree.size() << endl;
  cout << "RBTree root: " << rbtree.root->data << endl;
  // cout << "RBTree root left: " << rbtree.root->left->data << endl;
  // cout << "RBTree root right: " << rbtree.root->right->data << endl;
  if (rbtree.root->left) {
    cout << "RBTree root left: " << rbtree.root->left->data << endl;
  } else {
    cout << "RBTree root left: nullptr" << endl;
  }
  int index = 0;
  for (auto iter = rbtree.begin(); iter != rbtree.end(); ++iter, ++index) {
    cout << *iter << " ";
    cout << "index: " << index << endl;
  }
}

void log_test() {
  cout << "log(100, 10) = " << log(100, 10) << endl;
  cout << "log(1000, 10) = " << log(1000, 10) << endl;
  cout << "log(1024, 2) = " << log(1024, 2) << endl;
  cout << "log(1, 2) = " << log(1, 2) << endl;
  cout << "log(0, 2) = " << log(0, 2) << endl;
  cout << "log(2, 3) = " << log(2, 3) << endl;
  cout << "log(3, 2) = " << log(3, 2) << endl;
}

void alloc_test() {
  auto start = clock();
  const int N = 1000000;
  for (int i = 0; i < N; ++i) {
    void *p = STL::Alloc::allocate(20);
  }
  auto end = clock();
  cout << "my allocator spend time: " << end - start << endl;
  auto start2 = clock();
  for (int i = 0; i < N; ++i) {
    void *p = operator new(20);
  }
  auto end2 = clock();
  cout << "standard lib spend time: " << end2 - start2 << endl;
}

void hashtable_test() {
  HashTable<int> ht;
  ht.insert(1);
  ht.insert(2);
  ht.insert(3);
  ht.insert(4);
  ht.insert(5);
  ht.insert(6);
  ht.insert(7);
  ht.insert(8);
  ht.insert(9);
  ht.insert(10);
  cout << "Count 5: " << ht.count(5) << endl;
  cout << "Count 11: " << ht.count(11) << endl;
  ht.erase(5);
  cout << "Count 5 after erase: " << ht.count(5) << endl;
}

void deque_test() {
  My_Deque<int> dq;
  dq.push_back(1);
  cout << dq.back() << " ";
  dq.push_back(2);
  cout << dq.back() << " ";
  dq.push_back(3);
  cout << dq.back() << " ";
  dq.push_back(4);
  cout << dq.back() << " ";
  dq.push_front(0);
  cout << dq.back() << " " << endl;
}

int main() {
  // string_test();
  // vector_test();
  // list_test();
  // set_test();
  // rbtree_test();
  // log_test();
  // alloc_test();
  // hashtable_test();
  deque_test();
  return 0;
}
