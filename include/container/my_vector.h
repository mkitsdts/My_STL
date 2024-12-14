//
// Created by mkitsdts on 14/6/2024.
//

#ifndef MY_STL_MY_VECTOR_H
#define MY_STL_MY_VECTOR_H
#include "../allocator/Allocator.h"
#include "iostream"
namespace STL
{
	template <class value_type>
	class My_Vector_Iterator
	{
	public:
		My_Vector_Iterator(value_type* ptr)
		{
			this->_ptr = ptr;
		}
	public:
		My_Vector_Iterator operator++()
		{
			My_Vector_Iterator tmp = *this;
			++_ptr;
			return tmp;
		}
		My_Vector_Iterator operator++(int)
		{
			++_ptr;
			return *this;
		}
		My_Vector_Iterator operator--()
		{
			My_Vector_Iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		My_Vector_Iterator operator--(int)
		{
			--_ptr;
			return *this;
		}
		My_Vector_Iterator operator+(int n) const
		{
			return My_Vector_Iterator{ _ptr + n };
		}
		My_Vector_Iterator operator-(int n) const
		{
			return My_Vector_Iterator{ _ptr - n };
		}
		My_Vector_Iterator& operator+=(long long n)
		{
			_ptr += n;
			return *this;
		}
		My_Vector_Iterator& operator-=(long long n)
		{
			_ptr -= n;
			return *this;
		}
		long long operator -(const My_Vector_Iterator& it) const
		{
			return (_ptr - it._ptr);
		}
		value_type* operator->() const
		{
			return _ptr;
		}
		value_type& operator*() const
		{
			return *_ptr;
		}
		bool operator!=(const My_Vector_Iterator& it) const
		{
			return _ptr != it._ptr;
		}
		bool operator==(const My_Vector_Iterator& it) const
		{
			return _ptr == it._ptr;
		}
		bool operator<(const My_Vector_Iterator& it) const
		{
			return _ptr < it._ptr;
		}
		bool operator>(const My_Vector_Iterator& it) const
		{
			return _ptr > it._ptr;
		}
		bool operator<=(const My_Vector_Iterator& it) const
		{
			return _ptr <= it._ptr;
		}
		bool operator>=(const My_Vector_Iterator& it) const
		{
			return _ptr >= it._ptr;
		}
		value_type* _ptr;
	};

	template <class value_type>
	class My_Vector_Reverse_Iterator
	{
	public:
		My_Vector_Reverse_Iterator(value_type* ptr)
		{
			_ptr = ptr;
		}
	public:
		My_Vector_Reverse_Iterator operator++()
		{
			My_Vector_Reverse_Iterator tmp = *this;
			--_ptr;
			return tmp;
		}
		My_Vector_Reverse_Iterator operator++(int)
		{
			--_ptr;
			return *this;
		}
		My_Vector_Reverse_Iterator operator--()
		{
			My_Vector_Reverse_Iterator tmp = *this;
			++_ptr;
			return tmp;
		}
		My_Vector_Reverse_Iterator operator--(int)
		{
			++_ptr;
			return *this;
		}
		My_Vector_Reverse_Iterator operator+(int n)
		{
			_ptr = _ptr - n;
			return *this;
		}
		My_Vector_Reverse_Iterator operator-(int n)
		{
			_ptr = _ptr + n;
			return *this;
		}
		value_type& operator*()
		{
			return *_ptr;
		}
		value_type* operator->()
		{
			return _ptr;
		}
		value_type* _ptr;
	};

	template <class value_type,class alloc = STL::Allocator<value_type>>
	class My_Vector
	{
	public:
		My_Vector() :_begin(nullptr), _end(nullptr), _current(nullptr), _size(0), _capacity(0)
		{
		}
		My_Vector(size_t size) :_begin(nullptr), _end(nullptr), _current(nullptr), _size(0), _capacity(0)
		{
			init(size, value_type{});
		}
		My_Vector(size_t size, value_type initial) :_begin(nullptr), _end(nullptr), _current(nullptr), _size(0), _capacity(0)
		{
			init(size, initial);
		}
		~My_Vector()
		{
			if (_begin != nullptr)
			{
				alloc::destroy(_begin, _end);
				std::cout << "when destory, _capacity = " << _capacity << std::endl;
				alloc::deallocate(_begin, _capacity * sizeof(value_type));
			}
			_begin = nullptr;
			_end = nullptr;
			_current = nullptr;
			_size = 0;
			_capacity = 0;
		}
		
//api
	public:
		value_type front()
		{
			return *_begin;
		}
		value_type back()
		{
			return *_current;
		}
		My_Vector_Iterator<value_type> begin()
		{
			return My_Vector_Iterator(_begin + first);
		}
		My_Vector_Iterator<value_type> end()
		{
			return My_Vector_Iterator(_current);
		}
		My_Vector_Reverse_Iterator<value_type> rbegin()
		{
			return My_Vector_Reverse_Iterator<value_type>(_current);
		}
		My_Vector_Reverse_Iterator<value_type> rend()
		{
			return My_Vector_Reverse_Iterator<value_type>(_begin + first);
		}
		My_Vector_Iterator<value_type> at(size_t index)
		{
			return My_Vector_Iterator<value_type>(_begin + index - 1);
		}
		size_t capacity() const
		{
			return _capacity;
		}
		size_t size() const
		{
			return _size;
		}
		bool empty() const
		{
			if (_capacity)
				return false;
			return true;
		}
		value_type& operator[](size_t index)
		{
			return *(_begin + index);
		}
	public:
		void emplace(size_t pos, const value_type& value)
		{

		}
		void emplace(const My_Vector_Iterator<value_type>& pos, const value_type& value)
		{
			if (isFull())
			{
				resize((_capacity + 1) * size_t(2));
			}
			My_Vector_Iterator tmp = _current;
			while (tmp != pos)
			{
				*(tmp + 1) = *tmp;
				--tmp;
			}
			*pos = value;
		}
		void push_back(const value_type& value)
		{
			if (isFull())
			{
				resize((_capacity + 1) * default_resize);
			}
			++_size;
			_current = _begin + _size - 1;
			*_current = value;
			std::cout << "_begin: " << *_begin << std::endl;
			std::cout << "_current: " << *_current << std::endl;
			
		}
		void pop_back()
		{
			_current = _current - 1;
			--_size;
		}
		void clear()
		{
			_current = _begin;
			_size = 0;
		}
		My_Vector_Iterator<value_type> erase(size_t index)
		{
			My_Vector_Iterator<value_type> tmp(_begin + index);
			while (tmp != _current)
			{
				*tmp = *(tmp + 1);
				tmp = tmp + 1;
			}
			_current = _current - 1;
			_capacity = _capacity - 1;
			return My_Vector_Iterator<value_type>(_begin + index);
		}
		My_Vector_Iterator<value_type> erase(My_Vector_Iterator<value_type> pos)
		{
			My_Vector_Iterator<value_type> tmp = pos;
			while (tmp != _current)
			{
				*tmp = *(tmp + 1);
				tmp = tmp + 1;
			}
			_current = _current - 1;
			_capacity = _capacity - 1;
			return pos;
		}
		My_Vector_Iterator<value_type> erase(My_Vector_Iterator<value_type> first, My_Vector_Iterator<value_type> last)
		{
			My_Vector_Iterator<value_type> tmp1 = first;
			My_Vector_Iterator<value_type> tmp2 = last;
			while (tmp2 != _current)
			{
				*tmp1 = *(tmp2 + 1);
				tmp1 = tmp1 + 1;
				tmp2 = tmp2 + 1;
			}
			_current = _current - (last - first);
			_capacity = _capacity - (last - first);
			return first;
		}

		void resize(size_t newSize)
		{
			std::cout << "申请的个数：" << newSize << std::endl;

			value_type* tmp_begin = alloc::allocate(newSize);	
			value_type* tmp_origin_begin = _begin;
			_begin = tmp_begin;
			_end = _begin + newSize;
			if(_size <= 0)
			{
				_current = _begin;
			}
			else
			{
				_current = _begin + _size - 1;
			}
			_capacity = newSize;
			std::cout << "tmp_begin = " << tmp_begin << std::endl;
			std::cout << "_current = " << _current << std::endl;
			std::cout << "_end = " << _end << std::endl;
			if (tmp_origin_begin != nullptr)
			{
				std::cout << "正在进行拷贝" << std::endl;
				for (size_t i = 0; i < _size; ++i)
				{
					*(_begin + i) = *(tmp_origin_begin + i);
				}
				for (size_t i = newSize - 1; i >= _size; --i)
				{
					*(_begin + i) = value_type{};
				}
				std::cout << "拷贝结束" << std::endl;
			}
			if (tmp_origin_begin != nullptr)
			{
				alloc::deallocate(tmp_origin_begin, _size);
			}
		}
		void resize(size_t newSize, value_type value)
		{
			std::cout << "申请的个数：" << newSize << std::endl;

			value_type* tmp_begin = alloc::allocate(newSize);
			value_type* tmp_origin_begin = _begin;
			_begin = tmp_begin;
			_end = _begin + newSize;
			if (_size <= 0)
			{
				_current = _begin;
			}
			else
			{
				_current = _begin + _size - 1;
			}
			_capacity = newSize;
			std::cout << "tmp_begin = " << tmp_begin << std::endl;
			std::cout << "_current = " << _current << std::endl;
			std::cout << "_end = " << _end << std::endl;
			if (tmp_origin_begin != nullptr)
			{
				std::cout << "正在进行拷贝" << std::endl;
				for (size_t i = 0; i < _size; ++i)
				{
					*(_begin + i) = *(tmp_origin_begin + i);
				}
				for (size_t i = newSize - 1; i >= _size; --i)
				{
					*(_begin + i) = value;
				}
				std::cout << "拷贝结束" << std::endl;
			}
			if (tmp_origin_begin != nullptr)
			{
				alloc::deallocate(tmp_origin_begin, _size);
			}
		}
	public:
		void operator = (const My_Vector& vec)
		{
			if (this != &vec)
			{
				alloc::deallocate(_begin, _capacity);
				this->_begin = alloc::allocate(vec.size());
				this->_end = _begin + vec._capacity;
				this->_current = _begin + vec.size();
				this->_size = vec.size();
				this->_capacity = vec.capacity();
				auto tmp = _begin;
				auto tmp2 = vec.begin();
				for (size_t i = 0; i < vec.size(); ++i, ++tmp, ++tmp2)
				{
					*tmp = *tmp2;		
				}
			}
		}
	private:
		void allocate(size_t size)
		{
			_begin = alloc::allocate(size);
			_end = _begin + size;
			_current = _begin;
			_capacity += size;
		}
		void init(size_t size, value_type value)
		{
			allocate(size);
			_capacity = size;
			_size = size;
			auto tmp = _begin;
			for (size_t i = 0; i < size; ++i,++tmp)
			{
				*tmp = value;
			}
		}
		bool isFull()
		{
			if (_capacity <= _size)
			{
				return true;
			}
			return false;
		}
	private:
		enum { default_resize = 2 };
		enum { no_num = 0 };
		enum { first = 1 };
	private:
		value_type* _begin;
		value_type* _end;
		value_type* _current;
		size_t _size;
		size_t _capacity;
	};
}


#endif //MY_STL_MY_VECTOR_H
