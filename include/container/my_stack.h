#pragma once
#include "my_deque.h"

namespace MY_STL
{
    template <class value_type>
    class My_Stack
    {
    public:
        My_Stack() = default;
        ~My_Stack() = default;

        void push(const value_type& value)
        {
            _deque.push_back(value);
        }
        void pop()
        {
            _deque.pop_front();
        }
        value_type& top()
        {
            return _deque.front();
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
        My_Deque<value_type> _deque;
    };
}