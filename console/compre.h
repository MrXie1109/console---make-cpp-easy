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

        template <class F>
        auto map(F &&f) const -> Comprehension<decltype(f(vec[0]))>
        {
            Comprehension<decltype(f(vec[0]))> tmp;
            for (const T &item : vec)
                tmp.vec.push_back(f(item));
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

    template <template <class> class Cont, class T>
    Comprehension<T> make_compre(const Cont<T> &cont)
    {
        return Comprehension<T>(cont);
    }

    template <template <class> class Cont, class T>
    Comprehension<T> make_compre(Cont<T> &&cont)
    {
        return Comprehension<T>(std::move(cont));
    }

    template <template <class> class Cont, class T>
    Comprehension<T> make_compre(const Cont<T> &cont,
                                 size_t start_pos, size_t end_pos)
    {
        return Comprehension<T>(cont, start_pos, end_pos);
    }

    template <template <class> class Cont, class T>
    Comprehension<T> make_compre(Cont<T> &&cont,
                                 size_t start_pos, size_t end_pos)
    {
        return Comprehension<T>(std::move(cont), start_pos, end_pos);
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

    template <template <class> class Cont, class K, class V>
    Comprehension<std::pair<K, V>> make_compre(
        const Cont<std::pair<K, V>> &cont)
    {
        return Comprehension<std::pair<K, V>>(cont);
    }

    template <template <class> class Cont, class K, class V>
    Comprehension<std::pair<K, V>> make_compre(Cont<std::pair<K, V>> &&cont)
    {
        return Comprehension<std::pair<K, V>>(std::move(cont));
    }

    template <template <class> class Cont, class K, class V>
    Comprehension<std::pair<K, V>> make_compre(
        const Cont<std::pair<K, V>> &cont, size_t start_pos, size_t end_pos)
    {
        return Comprehension<std::pair<K, V>>(cont, start_pos, end_pos);
    }

    template <template <class> class Cont, class K, class V>
    Comprehension<std::pair<K, V>> make_compre(Cont<std::pair<K, V>> &&cont,
                                               size_t start_pos, size_t end_pos)
    {
        return Comprehension<std::pair<K, V>>(
            std::move(cont), start_pos, end_pos);
    }
}
