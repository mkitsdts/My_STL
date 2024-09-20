//
// Created by mkitsdts on 16/6/2024.
//

#ifndef MY_STL_ALLOCATE_H
#define MY_STL_ALLOCATE_H

#include "Alloc.h"

namespace STL
{
	template<class value_type>
	class Allocator
	{
	 public:
		Allocator() = default;
		~Allocator() = default;

		//分配内存
		static value_type* allocate(size_t n)
		{
			//申请n个T类型的内存
			if (n <= 0)
			{
				return nullptr;
			}
			else
			{
				return static_cast<value_type*>(Alloc::allocate(n * (size_t)sizeof(value_type)));
			}
		}
		static value_type* allocate()
		{
			//申请1个字节T类型的内存
			return static_cast<value_type*>(Alloc::allocate((size_t)sizeof(value_type)));
		}
		//释放内存
		static void deallocate(value_type* ptr, size_t n)
		{
			Alloc::deallocate(static_cast<void*>(ptr),static_cast<size_t>(n));
		}
		//构造
		static void construct(value_type*ptr)
		{
			new(ptr)value_type();
		}
		static void construct(value_type*ptr, const value_type& value)
		{
			new(ptr)value_type(value);
		}
		
		//析构
		static void destroy(value_type* ptr)
		{
			//写这段代码的时候发现了一个新的东西
			//就是说
			//如果我这样写 int a=0; int* b=&a; b->~int(); 是无法通过编译的
			//很有趣，后面再回头深究一下
			ptr->~T();
		}
		static void destroy(value_type* begin, value_type* end)
		{
			while (begin != end)
			{
				begin->~value_type();
				++begin;
			}
		}
	};
}
#endif //MY_STL_ALLOCATE_H
