#include "./allocator/Allocator.h"
#include "./container/my_vector.h"
#include "algorithm/Algorithm.h"
#include "./memory/memory.h"
#include <iostream>
#include <memory>
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
	My_Vector<int> v1(1000,0);
	My_Vector<int> v2(2000,2);

	// 内存初始化检查
	/*
	for (auto i = 0; i < 1000; ++i)
	{
		v1[i] = i;
		cout << v1[i] << " ";
	}
	cout << endl;
	for (auto i = 0; i < 2000; ++i)
	{
		v2[i] = i;
		cout << v2[i] << " ";
	}
	cout << endl;
	cout << "内存初始化检查完成" << endl;
	*/

	// 动态扩容检查
	for (auto i = 0; i < 1000; ++i)
	{
		v.push_back(i);
	}
	for (auto i = 0; i < 1000; ++i)
	{
		cout << v[i] << " ";
	}
	cout << "动态扩容检查完成" << endl;
	
	// 动态缩容检查
	for (auto i = 0; i < 500; ++i)
	{
		v.pop_back();
	}
	for (auto i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << v.size() << endl;
}

static void smart_ptr_test()
{
	my_shared_ptr<int> ptr(new int(1));
	my_shared_ptr<int> ptr2(ptr);
	my_shared_ptr<int> ptr3(ptr);
	my_unique_ptr<int> ptr4(new int(2));
	my_unique_ptr<int> ptr5(new int(3));
	my_unique_ptr<int> ptr6(new int(4));
	cout << *ptr << endl;
	cout << *ptr2 << endl;
	cout << *ptr3 << endl;
}

static void sort_test()
{
	My_Vector<int> v;
	for (size_t i = 0; i < 20; ++i)
	{
		v.push_back(rand());
	}
	//sort(v.begin(), v.end());
	for (size_t i = 0; i < 20; ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

int main()
{
	//allocator_test();
	//vector_test();
	//list_test();
	//smart_ptr_test();
	sort_test();
	return 0;
}