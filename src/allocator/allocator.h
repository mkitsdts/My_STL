//
// Created by mkitsdts on 16/6/2024.
//

#pragma once
#include "alloc.h"
namespace STL
{
	template<typename value_type>
	class Allocator
	{
	public:
		Allocator() = default;
		~Allocator() = default;

		// Ĭ������1��value_type�Ŀռ�
		static value_type* allocate()
		{
			return static_cast<value_type*>(Alloc::allocate((size_t)sizeof(value_type)));
		}
		// ����n��value_type�Ŀռ�
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

		// ָ���ͷ�n��value_type�Ŀռ�
		static void deallocate(value_type* ptr, size_t n)
		{
			Alloc::deallocate(static_cast<void*>(ptr),n);
		}

		// Ĭ���޲ι��캯��
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
