#pragma once

#include "allocator/allocator.h"
#include <cstring>
#include <ostream>
#include <istream>

namespace STL
{
	constexpr size_t STRING_MAX_SIZE = 999;

	class My_String_Iterator
	{
	public:
		My_String_Iterator() = default;
		My_String_Iterator(char* ptr) :_ptr(ptr)
		{
		}
		My_String_Iterator(const My_String_Iterator& it) :_ptr(it._ptr)
		{
		}
		~My_String_Iterator() = default;

		char& operator*()
		{
			return *_ptr;
		}
		char* operator->()
		{
			return _ptr;
		}
		My_String_Iterator& operator++()
		{
			++_ptr;
			return *this;
		}
		My_String_Iterator operator++(int)
		{
			My_String_Iterator temp = *this;
			++_ptr;
			return temp;
		}
		My_String_Iterator& operator--()
		{
			--_ptr;
			return *this;
		}
		My_String_Iterator operator--(int)
		{
			My_String_Iterator temp = *this;
			--_ptr;
			return temp;
		}
		bool operator==(const My_String_Iterator& it)
		{
			return _ptr == it._ptr;
		}
		bool operator!=(const My_String_Iterator& it)
		{
			return _ptr != it._ptr;
		}
		char* _ptr;
	};

	template<typename alloc = Allocator<char>>
	class My_String
	{
	public:
		using iterator = My_String_Iterator;
		using const_iterator = My_String_Iterator;
		My_String() :_begin(nullptr), _end(nullptr), _size(0)
		{
		}
		My_String(char* str)
		{
			size_t size = 0;
			while (*(str) != '\0' && size <= STRING_MAX_SIZE)
			{
				++_size;
				++size;
			}
			if (!size)
			{
				_begin = alloc::allocate(1);
				_begin[0] = '\0';
				_end = _begin;
			}
			else
			{
				_begin = alloc::allocate(_size);
				_end = _begin + _size - 1;
				for (size_t i = 0; i < _size; ++i)
				{
					_begin[i] = str[i];
				}
			}
		}
		My_String(const char* str) :_begin(const_cast<char*>(str)),_size(0)
		{
			size_t size = 0;
			while (*(str) != '\0' && size <= STRING_MAX_SIZE)
			{
				++_size;
				++size;
			}
			if (!size)
			{
				_begin = alloc::allocate(1);
				_begin[0] = '\0';
				_end = _begin;
			}
			else
			{
				_begin = alloc::allocate(_size);
				_end = _begin + _size - 1;
				for (size_t i = 0; i < _size; ++i)
				{
					_begin[i] = str[i];
				}
			}
		}
		My_String(const My_String& str) : _size(str.size())
		{
			_begin = alloc::allocate(_size);
			_end = _begin + _size - 1;
			for (size_t i = 0; i < _size; ++i)
			{
				_begin[i] = str[i];
			}
		}
		~My_String()
		{
			alloc::deallocate(_begin, _size);
		}
		int size()
		{
			return _size;
		}

		My_String& operator=(const My_String& str)
		{
			if (this == &str)
			{
				return *this;
			}
			alloc::deallocate(_begin, _size);
			_size = str.size();
			_begin = alloc::allocate(_size);
			_end = _begin + _size - 1;
			for (size_t i = 0; i < _size; ++i)
			{
				_begin[i] = str[i];
			}
			return *this;
		}
		My_String& operator=(const My_String&& str)
		{
			if (this == &str)
			{
				return *this;
			}
			alloc::deallocate(_begin, _size);
			_size = str.size();
			_begin = alloc::allocate(_size);
			_end = _begin + _size - 1;
			for (size_t i = 0; i < _size; ++i)
			{
				_begin[i] = str[i];
			}
			return *this;
		}
		My_String& operator=(char* str)
		{
			alloc::deallocate(_begin, _size);
			_size = 0;
			while (*(str) != '\0' && _size <= STRING_MAX_SIZE)
			{
				++_size;
				++str;
			}
			if (_size == STRING_MAX_SIZE)
			{
				_end = _begin + STRING_MAX_SIZE - 1;
				*str = '\0';
			}
			else
			{
				_end = _begin + _size - 1;
			}
			_begin = alloc::allocate(_size);
			for (size_t i = 0; i < _size; ++i)
			{
				_begin[i] = str[i];
			}
			return *this;
		}
		My_String& operator=(const char* str)
		{
			alloc::deallocate(_begin, _size);
			_size = 0;
			size_t size = 0;
			while (*(str) != '\0' && size <= STRING_MAX_SIZE)
			{
				++_size;
				++size;
			}
			if (!size)
			{
				_begin = alloc::allocate(1);
				_begin[0] = '\0';
				_end = _begin;
			}
			else
			{
				_begin = alloc::allocate(_size);
				_end = _begin + _size - 1;
				for (size_t i = 0; i < _size; ++i)
				{
					_begin[i] = str[i];
				}
			}
			return *this;
		}
		char operator[](size_t pos)
		{
			return _begin[pos];
		}
		iterator begin()
		{
			return iterator(_begin);
		}
		iterator end()
		{
			return iterator(_end);
		}
		friend std::ostream& operator <<(std::ostream& output, My_String<>& str);
		friend std::istream& operator >>(std::istream& input, My_String<>& str);


		char* _begin;
		char* _end;
		size_t _size;
	};

	std::ostream& operator <<(std::ostream& output, My_String<>& str)
	{
		output << str._begin;
		return output;
	}
	std::istream& operator >>(std::istream& input, My_String<>& str)
	{
		char s[256];
		input >> s;
		if(!str._begin)
			str._begin = new char[256];
		strcpy(str._begin,s);
		return input;
	}
}
