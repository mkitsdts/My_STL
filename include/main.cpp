#include "./base/hashtable.h"
#include <iostream>
using namespace STL;

int main()
{
	HashTable<int> set;
	set.insert(1);
	std::cout << set.count(1) << "\n";
	return 0;
}