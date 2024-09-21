//
// Created by mkitsdts on 14/6/2024.
//

#ifndef MY_STL_MY_VECTOR_H
#define MY_STL_MY_VECTOR_H
#include "../allocator/Allocator.h"

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
			iterator tmp = *this;
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
			iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		My_Vector_Iterator operator--(int)
		{
			--_ptr;
			return *this;
		}
		My_Vector_Iterator operator+(int n)
		{
			_ptr = _ptr + n;
			return *this;
		}
		My_Vector_Iterator operator-(int n)
		{
			_ptr = _ptr - n;
			return *this;
		}
		long long operator-(const My_Vector_Iterator& it)
		{
			return _ptr - it._ptr;
		}
		long long operator-(My_Vector_Iterator& it)
		{
			return _ptr - it._ptr;
		}
		value_type* operator->()
		{
			return _ptr;
		}
		bool operator!=(const iterator& it)
		{
			return _ptr != it._ptr;
		}
		bool operator==(const iterator& it)
		{
			return _ptr == it._ptr;
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
		My_Vector(size_t size)
		{
			init(size, value_type());
		}
		My_Vector(size_t size, value_type& initial)
		{
			init(size, initial);
		}
		~My_Vector()
		{
			Allocator<value_type>::destroy(_begin, _end);
			Allocator<value_type>::deallocate(_begin,_capacity);
			_begin = nullptr;
			_end = nullptr;
			_current = nullptr;
			_size = 0;
			_capacity = 0;
		}
		
//api
	public:
		value_type& front()
		{
			return *_begin;
		}
		value_type& back()
		{
			return *_current;
		}
		My_Vector_Iterator begin()
		{
			return _begin + first;
		}
		My_Vector_Iterator end()
		{
			return _current;
		}
		My_Vector_Reverse_Iterator rbegin()
		{
			return _current;
		}
		My_Vector_Reverse_Iterator rend()
		{
			return _begin + first;
		}
		My_Vector_Iterator at(size_t index)
		{
			return (_begin + index - 1);
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
			{
				return false;
			}
			return true;
		}
		value_type operator[](size_t index)
		{
			return *(_begin + index);
		}
	public:
		void emplace(My_Vector_Iterator pos,value_type& value)
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
		void push_back(value_type& value)
		{
			if (isFull())
			{
				resize((_capacity + 1) * size_t(2));
			}
			_current = _current + 1;
			*_current = value;
			_capacity = _capacity + 1;
		}
		void push_back(value_type value)
		{
			if (isFull())
			{
				resize((_capacity + 1) * size_t(2));
			}
			_current = _current + 1;
			*_current = value;
			_capacity = _capacity + 1;
		}
		void pop_back()
		{
			_current = _current - 1;
			_capacity = _capacity - 1;
		}
		void clear()
		{
			_current = _begin;
			_capacity = 0;
		}
		My_Vector_Iterator erase(size_t index)
		{
			My_Vector_Iterator tmp = _begin + index;
			while (tmp != _current)
			{
				*tmp = *(tmp + 1);
				tmp = tmp + 1;
			}
			_current = _current - 1;
			_capacity = _capacity - 1;
			return _begin + index;
		}
		My_Vector_Iterator erase(My_Vector_Iterator pos)
		{
			My_Vector_Iterator tmp = pos;
			while (tmp != _current)
			{
				*tmp = *(tmp + 1);
				tmp = tmp + 1;
			}
			_current = _current - 1;
			_capacity = _capacity - 1;
			return pos;
		}
		My_Vector_Iterator erase(My_Vector_Iterator first, My_Vector_Iterator last)
		{
			My_Vector_Iterator tmp1 = first;
			My_Vector_Iterator tmp2 = last;
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
			My_Vector_Iterator tmp_begin = My_Vector_Iterator(Allocator<value_type>::allocate(newSize));
			My_Vector_Iterator tmp_new_begin = tmp_begin;
			My_Vector_Iterator tmp_origin_begin = _begin;
			if (tmp_origin_begin != nullptr)
			{
				while (tmp_new_begin != _current)
				{
					*tmp_new_begin = *tmp_origin_begin;
					tmp_new_begin = tmp_new_begin + 1;
					tmp_origin_begin = tmp_origin_begin + 1;
				}
				size_t add_size = newSize / 2;
				while (add_size > 0)
				{
					*tmp_new_begin = value_type();
					add_size = add_size - 1;
				}
			}
			else
			{
				size_t add_size = newSize;
				while (add_size > 0)
				{
					*tmp_new_begin = value_type();
					add_size = add_size - 1;
				}
				_begin = tmp_begin;
				_end = _begin + newSize;
				_capacity = no_num;
				_current = tmp_begin;
				_size = newSize;
			}
		}
		void resize(size_t newSize, value_type value)
		{
			My_Vector_Iterator tmp_begin = My_Vector_Iterator(Allocator<value_type>::allocate(newSize));
			My_Vector_Iterator tmp_new_begin = tmp_begin;
			My_Vector_Iterator tmp_origin_begin = _begin;
			while (tmp_new_begin != _current)
			{
				*tmp_new_begin = *tmp_origin_begin;
				tmp_new_begin = tmp_new_begin + 1;
				tmp_origin_begin = tmp_origin_begin + 1;
			}
			size_t add_size = newSize / 2;
			while (add_size > 0)
			{
				*tmp_new_begin = value;
				add_size = add_size - 1;
			}
		}
	public:
		void operator = (const My_Vector& vec)
		{
			if (this != &vec)
			{
				Allocator::deallocate(_begin, _size);
				this->_begin = My_Vector_Iterator(Allocator<value_type>::allocate(vec.size()));
				this->_end = _begin + vec.size();
				this->_current = _begin;
				this->_size = vec.size();
				this->_capacity = vec.capacity();
				My_Vector_Iterator tmp = _begin;
				My_Vector_Iterator tmp2 = vec.begin();
				for (size_t i = 0; i < vec.size(); ++i)
				{
					*tmp = *tmp2;
					++tmp;
					++tmp2;
				}
			}
		}
	private:
		void allocate(size_t size)
		{
			_begin = My_Vector_Iterator(Allocator<value_type>::allocate(size));
			_end = _begin + size;
			_current = _begin;
		}
		void init(size_t size, value_type& value)
		{
			allocate(size);
			My_Vector_Iterator tmp = _begin;
			for (size_t i = 0; i < size; ++i)
			{
				*tmp = value;
				++tmp;
			}
		}
		bool isFull()
		{
			if (_capacity >= _size)
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
		My_Vector_Iterator _begin;
		My_Vector_Iterator _end;
		My_Vector_Iterator _current;
		size_t _size;
		size_t _capacity;
	};
}


#endif //MY_STL_MY_VECTOR_H
