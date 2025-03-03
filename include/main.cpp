#include <iostream>
#include <memory>

#include "container/my_string.h"
#include "container/my_vector.h"
#include "container/my_list.h"
#include "memory/memory.h"
using namespace STL;
using std::cout;
using std::endl;

void string_test()
{
    My_String str("hello world");
    cout << str << endl;
}

void vector_test()
{
    My_Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    cout << vec.size() << endl;
    cout << vec.capacity() << endl;
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void list_test()
{
    My_List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    cout << l.size() << endl;
    for(auto it = l.begin(); it != l.end(); ++it)
    {
        cout << *it << " ";
    }
}

int main() 
{
    string_test();
    vector_test();
    list_test();
	return 0;
}
