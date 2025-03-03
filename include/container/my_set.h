#pragma once
#include "allocator/allocator.h"
#include "base/rbtree.h"
#include <functional>

namespace STL
{
	template<class Key, class Compare = std::less<Key>, class Alloc = Allocator<Key>>
	class My_Set
	{
	public:
		using value_type = Key;
		struct My_Set_Node
		{
		public:
			My_Set_Node() :data(value_type()), left(nullptr), right(nullptr), parent(nullptr), color(0)
			{
			}
			My_Set_Node(const value_type& value) :data(value), left(nullptr), right(nullptr), parent(nullptr), color(0)
			{
			}
			~My_Set_Node()
			{
				operator delete(left);
				operator delete(right);
				operator delete(parent);
				left = nullptr;
				right = nullptr;
				parent = nullptr;
			}
			value_type data;
			My_Set_Node* left;
			My_Set_Node* right;
			My_Set_Node* parent;
			bool color;
		};
		struct My_Set_Iterator
		{
			My_Set_Iterator(My_Set_Node* ptr) :_ptr(ptr)
			{
			}
			My_Set_Iterator operator++()
			{
				My_Set_Iterator tmp = *this;
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
					{
						_ptr = _ptr->left;
					}
				}
				else
				{
					while (_ptr->parent && _ptr->parent->right == _ptr)
					{
						_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
				}
				return tmp;
			}
			My_Set_Iterator operator++(int)
			{
				if (_ptr->right)
				{
					_ptr = _ptr->right;
					while (_ptr->left)
					{
						_ptr = _ptr->left;
					}
				}
				else
				{
					while (_ptr->parent && _ptr->parent->right == _ptr)
					{
						_ptr = _ptr->parent;
					}
					_ptr = _ptr->parent;
				}
				return *this;
			}
			value_type& operator*()
			{
				return _ptr->data;
			}
			value_type* operator->()
			{
				return &_ptr->data;
			}
			bool operator==(const My_Set_Iterator& it)
			{
				return _ptr == it._ptr;
			}
			bool operator!=(const My_Set_Iterator& it)
			{
				return _ptr != it._ptr;
			}
			My_Set_Node* _ptr;
		};
	public:
		void insert(value_type& value)
		{
			tree.insert(value);
			
		}
		void insert(const value_type& value)
		{
			tree.insert(value);
		}
		void erase(value_type& value)
		{
			tree.erase(value);
		}
		void erase(const value_type& value)
		{
			tree.erase(value);
		}
		void clear()
		{
			tree.clear();
		}
		size_t size()
		{
			return tree.size();
		}
		bool empty()
		{
			return tree.empty();
		}
		bool find(value_type& value)
		{
			return tree.find(value);
		}
		bool find(const value_type& value)
		{
			return tree.find(value);
		}
		My_Set_Iterator begin()
		{
			My_Set_Node* cur = new My_Set_Node{tree.root->data};
			while (cur->left)
			{
				cur = cur->left;
			}
			return My_Set_Iterator(cur);
		}
		My_Set_Iterator end()
		{
			return My_Set_Iterator(nullptr);
		}
	private:
		RBTree<Key> tree;
	};
}