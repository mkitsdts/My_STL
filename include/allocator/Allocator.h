//
// Created by mkitsdts on 16/6/2024.
//

#ifndef MY_STL_ALLOCATE_H
#define MY_STL_ALLOCATE_H

#include "Alloc.h"
namespace STL
{
	template<typename value_type>
	class Allocator
	{
	public:
		Allocator() = default;
		~Allocator() = default;

		// 默认申请1个value_type的空间
		static value_type* allocate()
		{
			return static_cast<value_type*>(Alloc::allocate((size_t)sizeof(value_type)));
		}
		// 申请n个value_type的空间
		static value_type* allocate(const size_t& n)
		{
			if (n <= 0)
			{
				return nullptr;
			}
			else
			{
				return static_cast<value_type*>(Alloc::allocate(n * (size_t)sizeof(value_type)));
			}
		}

		// 指定释放n个value_type的空间
		static void deallocate(value_type* ptr, size_t n)
		{
			Alloc::deallocate(static_cast<void*>(ptr),n);
		}

		// 默认无参构造函数
		static void construct(value_type* ptr)
		{
			new(ptr)value_type{};
		}
		static void construct(value_type* ptr, const value_type& value)
		{
			new(ptr)value_type{ value };
		}
		
		static void destroy(value_type* ptr)
		{
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
