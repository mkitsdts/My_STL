#include <iostream>

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
  for (auto it = l.begin(); it != l.end(); ++it) {
    cout << *it << " ";
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

int main() {
  // string_test();
  // vector_test();
  // list_test();
  set_test();
  return 0;
}
