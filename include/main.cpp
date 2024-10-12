#include "./memory/memory.h"
#include <iostream>
using namespace STL;

int main()
{
	int a = 10;
	int* b = &a;
	my_shared_ptr<int> ptr(b);
	std::cout << (*ptr) << "\n";
	return 0;
}