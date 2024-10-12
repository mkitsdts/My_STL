#ifndef MEMORY_H
#define MEMORY_H

namespace STL
{
	class Counter
	{
	public:
		Counter() :_count(0)
		{
		}
		~Counter()
		{
		}
		void operator++()
		{
			++_count;
		}
		void operator--()
		{
			--_count;
		}
		void operator++(int)
		{
			++_count;
		}
		void operator--(int)
		{
			--_count;
		}
		int use_count() const noexcept
		{
			return _count;
		}
	private:
		int _count;
	};

	template <class T,class counter = Counter>
	class shared_ptr
	{
		using pointer = T*;
	public:
		explicit shared_ptr() :_ptr(nullptr) 
		{
		}
		explicit shared_ptr(pointer ptr) :_ptr(ptr), _count(1)
		{
		}
		explicit shared_ptr(const shared_ptr& other) :_ptr(other._ptr), _count(other._count)
		{
		}
		~shared_ptr()
		{
			delete _ptr;
		}
		shared_ptr& operator=(shared_ptr& other)
		{
			_ptr = other.get();
			_count = other._count;
			++_count;
			return *this;
		}
		pointer get() const noecxept
		{
			return _ptr;
		}
		int use_count() const noexcept
		{
			return _count;
		}
		template <class Other>
		void reset(Other* ptr)
		{
			delete _ptr;
			_ptr = ptr;
			_count = 1;
		}
	private:
		pointer _ptr;
		int _count;
	};

	template <class T>
	shared_ptr<T> make_shared()
	{
		return shared_ptr<T>();
	}
}

#endif // !MEMORY_H
