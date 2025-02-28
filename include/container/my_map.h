#pragma once
#define MY_MAP_H
#include "base/pair.h"
#include "my_set.h"
#include "allocator/Allocator.h"

/*һ��������Ψһ���Ӧ��һ��ֵ*/
namespace STL
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = Allocator<pair<Key,T>>>
	class My_Map
	{
	public:
		My_Map() = default;
		~My_Map() = default;
		My_Map(const My_Map& other) :tree(other.tree) {}
		My_Map(My_Map&& other) noexcept :tree(std::move(other.tree)) {}
		My_Map& operator=(const My_Map& other)
		{
			tree = other.tree;
			return *this;
		}
		My_Map& operator=(My_Map&& other) noexcept
		{
			tree = std::move(other.tree);
			return *this;
		}
		void insert(const pair<Key, T>& value)
		{
			tree.insert(value);
		}
		void insert(pair<Key, T>&& value)
		{
			tree.insert(std::move(value));
		}
		void insert(Key key, T value)
		{
			tree.insert(pair<Key, T>(key, value));
		}
		void erase(const Key& key)
		{
			tree.erase(pair<Key, T>(key, T()));
		}
		void clear()
		{
			tree.clear();
		}
	private:
		My_Set<pair<Key, T>, Compare, Alloc> tree;
	};
}

