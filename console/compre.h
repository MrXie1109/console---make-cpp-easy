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
#include <vector>
#include <utility>
#include <iterator>

namespace console
{
    template <class T>
    class Comprehension
    {
    protected:
        std::vector<T> vec;

    public:
        Comprehension() : vec() {}

        template <class Cont>
        Comprehension(const Cont &cont)
            : vec(std::begin(cont), std::end(cont)) {}

        template <class Cont>
        Comprehension(Cont &&cont)
            : vec(
                  std::make_move_iterator(std::begin(cont)),
                  std::make_move_iterator(std::end(cont))) {}

        template <class Cont>
        Comprehension(const Cont &cont, size_t start_pos, size_t end_pos)
            : vec(std::next(std::begin(cont), start_pos),
                  std::next(std::begin(cont), end_pos)) {}

        template <class Cont>
        Comprehension(Cont &&cont, size_t start_pos, size_t end_pos)
            : vec(std::make_move_iterator(
                      std::next(std::begin(cont), start_pos)),
                  std::make_move_iterator(
                      std::next(std::begin(cont), end_pos))) {}

        template <class Iter>
        Comprehension(Iter beg, Iter end) : vec(beg, end) {}

        Comprehension(std::initializer_list<T> init) : vec(init) {}

        std::vector<T> &get_vec()
        {
            return vec;
        }

        template <class F>
        auto map(F &&f) const -> Comprehension<decltype(f(vec[0]))>
        {
            Comprehension<decltype(f(vec[0]))> tmp;
            for (const T &item : vec)
                tmp.get_vec().push_back(f(item));
            return tmp;
        }

        template <class F>
        Comprehension<T> filter(F &&f) const
        {
            Comprehension<T> tmp;
            for (const T &item : vec)
                if (f(item))
                    tmp.vec.push_back(item);
            return tmp;
        }

        template <class Cont>
        Cont to()
        {
            return Cont(
                std::make_move_iterator(vec.begin()),
                std::make_move_iterator(vec.end()));
        }

        template <class Cont>
        Cont make() const
        {
            return Cont(vec.begin(), vec.end());
        }
    };

    template <class Cont>
    auto make_compre(const Cont &cont)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(cont);
    }

    template <class Cont>
    auto make_compre(Cont &&cont)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(std::move(cont));
    }

    template <class Cont>
    auto make_compre(const Cont &cont, size_t start_pos, size_t end_pos)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(
            cont, start_pos, end_pos);
    }

    template <class Cont>
    auto make_compre(Cont &&cont, size_t start_pos, size_t end_pos)
        -> Comprehension<typename Cont::value_type>
    {
        return Comprehension<typename Cont::value_type>(
            std::move(cont), start_pos, end_pos);
    }

    template <class Iter>
    auto make_compre(Iter beg, Iter end) -> Comprehension<decltype(*beg)>
    {
        return Comprehension<decltype(*beg)>(beg, end);
    }

    template <class T>
    Comprehension<T> make_compre(std::initializer_list<T> init)
    {
        return Comprehension<T>(init);
    }
}
