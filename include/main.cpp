#include "allocator/Allocator.h"
#include "container/my_string.h"
#include "memory/memory.h"
#include <iostream>
#include <memory>
using namespace STL;
using std::cout;
using std::endl;

int main()
{
	My_String str1("hello");
	cout << str1 << endl;
	str1 = "world";
	cout << str1 << endl;
	return 0;
}