#include "./allocator/Allocator.h"
#include "./container/my_vector.h"
#include <iostream>
using namespace STL;
using std::cout;
using std::endl;

static void allocator_test()
{
	int* ptr = Allocator<int>::allocate(1000);
	for(int i = 0; i<10;++i)
	{
		int* ptr = Allocator<int>::allocate(4);
		int* ptr2 = Allocator<int>::allocate(4);
		cout << ptr << " " << ptr2 << endl;
		cout << ptr2 - ptr << endl;					//预期输出4
	}
	for (size_t i = 0; i < 1000; ++i)
	{
		Allocator<int>::construct(ptr+i, 1000);
		std::cout << ptr + i << std::endl;
		std::cout << *(ptr + i) << std::endl;
	}
	Allocator<int>::destroy(ptr,ptr+1000);
	Allocator<int>::deallocate(ptr, 1000);
}

static void vector_test()
{
	My_Vector<int> v;
	My_Vector<int> v1(1000);
	My_Vector<int> v2(2000,2);
	cout << v.size() << endl;
	cout << v1.size() << endl;
	cout << v2.size() << endl;
	for (size_t i = 0; i < 1000; ++i)
	{
		//cout << v1[i] << " " << v2[i] << endl;
	}
	//预期输出3
	int a = 3;
	v.push_back(a);
	v2.push_back(a);
	cout << v[0] << endl;
	cout << *v1.rend() << endl;
	cout << v1.size() << endl;
}

int main()
{
	//allocator_test();
	vector_test();
	return 0;
}