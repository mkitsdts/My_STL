#include "./base/RBTree.h"
#include <iostream>
using namespace STL;

int main()
{
	RBTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(1);
	tree.insert(4);
	tree.insert(2);
	std::cout << tree.empty() << std::endl;
	if (tree.find(3))
	{
		std::cout << "find 3" << std::endl;
	}
	return 0;
}