#pragma once
#include "my_deque.h"

namespace MY_STL
{
    template <typename value_type>
    class My_Queue
    {
    public:
        struct node
        {
            value_type data;
            node *next;
        };
        My_Queue():_size(0),_capacity(0),_front(nullptr),_back(nullptr)
        {
        }

        void push(const value_type& value)
        {
            _deque.push_back(value);
        }
        void pop()
        {
            _deque.pop_front();
        }
        value_type& front()
        {
            return _deque.front();
        }
        value_type& back()
        {
            return _deque.back();
        }
        size_t size()
        {
            return _deque.size();
        }
        bool empty()
        {
            return _deque.empty();
        }
    private:
        my_deque<value_type> _deque;
    };
}