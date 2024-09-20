#pragma once
#ifndef MY_SET_H
#define MY_SET_H
#include "Allocator.h"
#include "Iterator.h"
#include "red_black_tree.h"
namespace STL
{
	template<class T>
	class My_Set_Node:public RBNode<T>
	{
		public:
		My_Set_Node()
		{
			data = T();
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			color = 0;
		}
		My_Set_Node(T& value)
		{
			data = value;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			color = 0;
		}
		My_Set_Node(const T& value)
		{
			data = value;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			color = 0;
		}
		~My_Set_Node()
		{
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
	public:

	private:
		T data;
		My_Set_Node* left;
		My_Set_Node* right;
		My_Set_Node* parent;
		bool color;
	};

	//ºìºÚÊ÷
	template<class Key, class Compare = std::less<Key>, class Alloc = Allocator<Key>>
	class My_Set:public RBTree<Key, Compare, Alloc>
	{
	public:
		using value_type = Key;

	public:
		void insert(value_type& value)
		{

		}
		void insert(const value_type& value)
		{

		}
	private:
		My_Set_Node<Key>* root;
		size_t size;
	};
}

#endif // !MY_SET_H