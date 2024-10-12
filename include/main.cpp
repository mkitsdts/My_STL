#include "./container/my_list.h"
#include <iostream>
using namespace STL;

int main()
{
	My_List<int> list;
	list.push_back(1);
	std::cout << list.front() << "\n";
	return 0;
}