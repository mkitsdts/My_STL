#ifndef MEMORY_H
#define MEMORY_H

#include <atomic>

namespace STL
{
	template <class T>
	class my_shared_ptr
	{
		using value_type = T;
		using pointer = T*;
	public:
		explicit my_shared_ptr() :_ptr(nullptr), _count(new std::atomic<int>(0))
		{
		}
		explicit my_shared_ptr(pointer ptr) :_ptr(ptr), _count(new std::atomic<int>(1))
		{
		}
		explicit my_shared_ptr(my_shared_ptr& other) : _ptr(other._ptr), _count(other._count)
		{
			if(_ptr)
				++(*_count);
		}
		explicit my_shared_ptr(const my_shared_ptr& other) :_ptr(other._ptr), _count(other._count)
		{
			if (_ptr)
				++(*_count);
		}
		~my_shared_ptr()
		{
			--(*_count);
			if(!(*_count))
			{
				delete _count;
				delete _ptr;
			}
		}
		my_shared_ptr<T>& operator=(my_shared_ptr<T>& other)
		{
			if (this != &other)
			{
				if (_ptr)
				{
					if ((--(*_count)) <= 0)
					{
						~my_shared_ptr();
					}
				}
				_ptr = other._ptr;
				_count = other._count;
				++(*_count);
			}
			return *this;
		}
		pointer get() const noexcept
		{
			return _ptr;
		}
		pointer operator->() const noexcept
		{
			return _ptr;
		}
		value_type& operator*() const noexcept
		{
			return *_ptr;
		}
		pointer _ptr;
		std::atomic<int>* _count;	
	};

	template <class T>
	my_shared_ptr<T> make_shared()
	{
		return my_shared_ptr<T>();
	}
	
	template <class T>
	my_shared_ptr<T> make_shared(T* ptr)
	{
		return my_shared_ptr<T>(ptr);
	}

	template <class T>
	class my_unique_ptr
	{
		using value_type = T;
		using pointer = T*;
	public:
		
	};
}

#endif // !MEMORY_H
