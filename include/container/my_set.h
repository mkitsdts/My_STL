#pragma once
#ifndef MY_SET_H
#define MY_SET_H
#include "../allocator/Allocator.h"
#include "../base/RBTree.h"

namespace STL
{
	//ºìºÚÊ÷
	template<class Key, class Compare = std::less<Key>, class Alloc = Allocator<Key>>
	class My_Set
	{
	public:
		using value_type = Key;
		class My_Set_Node
		{
		public:
			My_Set_Node() :data(value_type()), left(nullptr), right(nullptr), parent(nullptr), color(0)
			{
			}
			My_Set_Node(value_type& value) :data(value), left(nullptr), right(nullptr), parent(nullptr), color(0)
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
		private:
			value_type data;
			My_Set_Node* left;
			My_Set_Node* right;
			My_Set_Node* parent;
			bool color;
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
	private:
		RBTree<Key, Compare, Alloc> tree;
		size_t size;
	};
}

#endif // !MY_SET_H