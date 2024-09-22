#ifndef MY_STL_MY_STACK_H
#define MY_STL_MY_STACK_H

#include "my_vector.h"

namespace MY_STL
{
    template <typename value_type>
    class My_Stack
    {
    public:
        My_Stack() = default;
        ~My_Stack() = default;

        void push(const value_type& value)
        {
            _vector.push_back(value);
        }
        void pop()
        {
            _vector.pop_back();
        }
        value_type& top()
        {
            return _vector.back();
        }
        size_t size()
        {
            return _vector.size();
        }
        bool empty()
        {
            return _vector.empty();
        }
    private:
        My_Vector<value_type> _vector;
    };
}

#endif //MY_STL_MY_STACK_H