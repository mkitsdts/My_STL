#include <iostream>

#include "algorithm/algorithm.h"
#include "base/rbtree.h"
#include "container/my_list.h"
#include "container/my_set.h"
#include "container/my_string.h"
#include "container/my_vector.h"

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

int main() {
  // string_test();
  // vector_test();
  // list_test();
  // set_test();
  // rbtree_test();
  log_test();
  return 0;
}
