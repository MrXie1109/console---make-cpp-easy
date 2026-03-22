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
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <valarray>
#include <utility>

namespace console
{
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::vector<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::deque<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::list<T> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::forward_list<T> &);
    template <class T, size_t n>
    std::ostream &operator<<(std::ostream &, const std::array<T, n> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::set<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::map<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::multiset<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::multimap<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::unordered_set<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::unordered_map<K, V> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::unordered_multiset<T> &);
    template <class K, class V>
    std::ostream &operator<<(std::ostream &, const std::unordered_multimap<K, V> &);
    template <class T, class U>
    std::ostream &operator<<(std::ostream &, const std::pair<T, U> &);
    template <class... Args>
    std::ostream &operator<<(std::ostream &, const std::tuple<Args...> &);
    template <class T>
    std::ostream &operator<<(std::ostream &, const std::valarray<T> &);
}
