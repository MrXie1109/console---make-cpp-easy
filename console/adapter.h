/**
 * @file adapter.h
 * @brief
 * @details
 * @author MrXie1109
 * @date 2026
 * @copyright MIT License
 */

/*
Copyright (c) 2026 MrXie1109

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include <deque>
#include <stack>
#include <queue>
#include <vector>
#include <utility>

namespace console
{
    template <class T, class Container = std::deque<T>>
    class Stack : public std::stack<T, Container>
    {
        using base_type = std::stack<T, Container>;

    public:
        using base_type::stack;

        typename base_type::value_type pop()
        {
            auto top = std::move(base_type::top());
            base_type::pop();
            return top;
        }
    };

    template <class T, class Container = std::deque<T>>
    class Queue : public std::queue<T, Container>
    {
        using base_type = std::queue<T, Container>;

    public:
        using base_type::queue;

        typename base_type::value_type pop()
        {
            auto top = std::move(base_type::front());
            base_type::pop();
            return top;
        }
    };

    template <class T, class Container = std::vector<T>,
              class Compare = std::less<typename Container::value_type>>
    class PriorityQueue : public std::priority_queue<T, Container, Compare>
    {
        using base_type = std::priority_queue<T, Container, Compare>;

    public:
        using base_type::priority_queue;

        typename base_type::value_type pop()
        {
            auto top = std::move(base_type::top());
            base_type::pop();
            return top;
        }
    };
}
