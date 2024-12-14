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
	inline my_shared_ptr<T> make_my_shared(T* ptr)
	{
		return my_shared_ptr<T>(ptr);
	}

	template <class T>
	class my_unique_ptr
	{
		using value_type = T;
		using pointer = T*;
	public:
		explicit my_unique_ptr() :_ptr(nullptr)
		{
		}
		explicit my_unique_ptr(pointer ptr)
		{
			_ptr = ptr;
		}
		explicit my_unique_ptr(my_unique_ptr& other) = delete;
		explicit my_unique_ptr(const my_unique_ptr& other) = delete;
		~my_unique_ptr()
		{
			delete _ptr;
		}
		my_unique_ptr<T>& operator=(my_unique_ptr<T>& other)
		{
			if (this != &other)
			{
				if (_ptr)
				{
					delete _ptr;
				}
				_ptr = other._ptr;
				other._ptr = nullptr;
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
	};

	template <class T>
	inline my_unique_ptr<T> make_my_unique(T* ptr)
	{
		return my_unique_ptr<T>(ptr);
	}

	/*template <class T>
	class my_weak_ptr
	{
		using value_type = T;
		using pointer = T*;
	public:
		friend my_shared_ptr make_my_weak(const my_shared_ptr& shared_ptr);
		void lock()
		{

		}
	private:
		explicit my_weak_ptr(const my_shared_ptr& shared_ptr)
		{

		}
	};*/

	/*template <class T>
	inline my_shared_ptr<T> make_my_weak(const my_shared_ptr<T>& shared_ptr)
	{
		return my_weak_ptr<T>{shared_ptr};
	}*/
}
#endif // !MEMORY_H
