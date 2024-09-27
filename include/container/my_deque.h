#ifndef MY_STL_MY_DEQUE_H
#define MY_STL_MY_DEQUE_H

#include "../allocator/Allocator.h"

namespace STL
{
    constexpr auto REDUNDANCY_TIMES = 1.6;
    constexpr auto BEGIN_SIZE_TIMES = 0.3;
    constexpr auto ADJUST_TIMES = 1.5;

    template <typename value_type>
    class My_Deque_Iterator
    {
    public:
        My_Deque_Iterator()
        {
        }
        My_Deque_Iterator(value_type* ptr)
        {
            _ptr = ptr;
        }
        My_Deque_Iterator operator=(const My_Deque_Iterator& iterator)
        {
            _ptr = iterator._ptr;
            return *this;
        }
        My_Deque_Iterator operator++()
        {
            My_Deque_Iterator tmp = *this;
            ++_ptr;
            return tmp;
        }
        My_Deque_Iterator operator++(int)
        {
            ++_ptr;
            return *this;
        }
        My_Deque_Iterator operator--()
        {
            My_Deque_Iterator tmp = *this;
            --_ptr;
            return tmp;
        }
        My_Deque_Iterator operator--(int)
        {
            --_ptr;
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

    template <typename value_type>
    class My_Deque_Reverse_Iterator
    {
    public:
        My_Deque_Reverse_Iterator()
        {
        }
        My_Deque_Reverse_Iterator(value_type* ptr)
        {
            _ptr = ptr;
        }
        My_Deque_Reverse_Iterator operator=(const My_Deque_Reverse_Iterator& iterator)
        {
            _ptr = iterator._ptr;
            return *this;
        }
        My_Deque_Reverse_Iterator operator++()
        {
            My_Deque_Reverse_Iterator tmp = *this;
            --_ptr;
            return tmp;
        }
        My_Deque_Reverse_Iterator operator++(int)
        {
            --_ptr;
            return *this;
        }
        My_Deque_Reverse_Iterator operator--()
        {
            My_Deque_Iterator tmp = *this;
            ++_ptr;
            return tmp;
        }
        My_Deque_Reverse_Iterator operator--(int)
        {
            ++_ptr;
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

    template <typename value_type>
    class My_Deque
    {
        using iterator = My_Deque_Iterator<value_type>;
        using reverse_iterator = My_Deque_Reverse_Iterator<value_type>;
    public:
        My_Deque():_begin(nullptr),_end(nullptr),_size(0),_capacity(0)
        {
        }
        My_Deque(size_t size):_begin(Allocator<value_type>::allocate(size*REDUNDANCY_TIMES)),_end(_begin+size*REDUNDANCY_TIMES)
        _front(iterator(_begin + BEGIN_SIZE_TIMES * size)),_back(iterator(*_front + size)),_size(size),_capacity(size*REDUNDANCY_TIMES)
        {
            fillData(value_type());
        }
        My_deque(size_t size, const value_type value):_begin(Allocator<value_type>::allocate(size*REDUNDANCY_TIMES)),_end(_begin+size*REDUNDANCY_TIMES)
        _front(iterator(_begin + BEGIN_SIZE_TIMES * size)),_back(iterator(*_front + size)),_size(size),_capacity(size*REDUNDANCY_TIMES)
        {
            fillData(value);
        }
        My_Deque(const My_Deque& deque):_begin(Allocator<value_type>::allocate(deque._capacity)),_end(_begin+deque._capacity)
        _front(iterator(_begin + (*(deque._front) - _begin))),_back(iterator(*_front + queue._size)),_size(queue._size),_capacity(deque._capacity)
        {
            auto write = _front;
            auto read = deque._front; 
            while(read != deque._back)
            {
                *write=*read;
                ++write;
                ++read;
            }
        }
        ~My_Deque()
        {
        }
    //api
    public:
        void push_back(value_type& value)
        {
            if(_size >= _capacity || *_back == _end)
            {
                adjust();
            }
            *_back = value;
            ++_back;
            ++_size;
        }
        void push_front(value_type& value)
        {
            if(_size >= _capacity || *_front == _begin)
            {
                adjust();
            }
            --_front;
            *_front = value;
            ++_size;
        }
        
        void pop_back()
        {
            if(_size == 0)
            {
                return;
            }
            *(--_back) = value_type();
            --_size;
        }
        void pop_front()
        {
            if(_size == 0)
            {
                return;
            }
            *_front = value_type();
            ++_front;
            --_size;
        }

        value_type& front()
        {
            return *_front;
        }
        value_type& back()
        {
            return *(--_back);
        }

        void emplace(iterator pos,value_type& value)
        {
            if(_size >= _capacity || *_back == _end)
            {
                adjust();
            }
            auto write = _back;
            auto read = _back - 1;
            while(write != pos)
            {
                *write = *read;
                --write;
                --read;
            }
            *pos = value;
        }
        void emplace(iterator pos,value_type&& value)
        {
            if(_size >= _capacity || *_back == _end || *_front == _begin)
            {
                adjust();
            }
            auto write = _back;
            auto read = _back - 1;
            while(write != pos)
            {
                *write = *read;
                --write;
                --read;
            }
            *pos = value;
        }
        void emplace_back(value_type& value)
        {
            if(_size >= _capacity || *_back == _end)
            {
                adjust();
            }
            *_back = value;
            ++_back;
            ++_size;
        }
        void emplace_back(value_type&& value)
        {
            if(_size >= _capacity || *_back == _end)
            {
                adjust();
            }
            *_back = value;
            ++_back;
            ++_size;
        }
        void emplace_front(value_type& value)
        {
            if(_size >= _capacity || *_front == _begin)
            {
                adjust();
            }
            --_front;
            *_front = value;
            ++_size;
        }
        void emplace_front(value_type&& value)
        {
            if(_size >= _capacity || *_front == _begin)
            {
                adjust();
            }
            --_front;
            *_front = value;
            ++_size;
        }

        iterator begin()
        {
            return _front;
        }
        iterator end()
        {
            return _back + 1;
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(*_back);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(*(_front - 1));
        }

        void resize(size_t size)
        {
            if(size == _size)
            {
                return;
            }
            if(size < _size)
            {
                dealloc(_begin + size);
                _size = size;
                _capacity = size;
                _back = _begin + size;
                _end = _begin + size;
                return;
            }
            begin = Allocator<value_type>::allocate(size);
            for(auto i = 0;i<size;++i)
            {
                *(begin+i)=*(_begin+i);
                ++begin;
                ++_begin;
            }
            Allocator::dealloc(_begin,_capacity);
            _begin=begin;
            _end=_begin+size;
            _size=size;
            _capacity=size;
            _front=iterator(_begin);
            _back=_front+size;
        }

        void clear()
        {
            if(!_end)
                return;
            --_back;
            while(_back!=_front)
            {
                *_back=value_type();
                --_back;
            }
            *_front=value_type();
        }

        void insert(iterator pos, value_type& value)
        {
            emplace(pos,value);
        }
        void insert(iterator pos, value_type&& value)
        {
            emplace(pos,value);
        }

        void erase(iterator pos)
        {
            for(auto iter=pos;(iter+1)!=_back;++iter)
            {
                *iter=*(iter+1);
            }
            --_size;
            --_back;
        }

        bool empty()
        {
            return _size == 0;
        }

        size_t size()
        {
            return _size;
        }

        My_Deque_Iterator<value_type> _front;
        My_Deque_Iterator<value_type> _back;
        value_type* _begin;
        value_type* _end;
        size_t _size;
        size_t _capacity;
    private:
        void fillData(value_type value)
        {
            for(size_t i = 0; i < _size; i++)
            {
                *(_front + i) = value;
            }
        }

        void adjust()
        {
            auto new_capacity = _capacity * ADJUST_TIMES;
            auto new_begin = Allocator<value_type>::allocate(new_capacity);
            auto new_front = iterator(new_begin + ((new_capacity - _size) / 2));
            auto new_back = new_front + _size;
            auto write = new_front;
            auto read = _front;
            while(read != _back)
            {
                *write = *read;
                ++write;
                ++read;
            }
            Allocator<value_type>::dealloc(_begin,_capacity);
            _begin = new_begin;
            _end = new_begin + new_capacity;
            _front = iterator(new_front);
            _back = iterator(new_back);
            _capacity = new_capacity;
        }
    };
}

#endif //MY_STL_MY_DEQUE_H