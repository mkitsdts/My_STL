#include "./container/my_vector.h"
#include <iostream>
using namespace STL;

int main()
{
	My_Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	std::cout<<vec.size()<<std::endl;
	return 0;

}