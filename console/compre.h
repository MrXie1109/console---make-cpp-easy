#pragma once
#include <vector>
#include <utility>

namespace console
{
    using namespace std;

    template <class OT, class IT, class F1, class F2>
    OT compre_mf(F1 &&expression, IT &&range, F2 &&requirement)
    {
        vector<decltype(expression(*begin(range)))> vec;
        for (auto item : forward<IT>(range))
            if (requirement(item))
                vec.push_back(expression(item));
        OT result(vec.size());
        copy(vec.begin(), vec.end(), begin(result));
        return result;
    }

    template <class OT, class IT, class F>
    OT compre_m(F &&expression, IT &&range)
    {
        vector<decltype(expression(*begin(range)))> vec;
        for (auto item : forward<IT>(range))
            vec.push_back(expression(item));
        OT result(vec.size());
        copy(vec.begin(), vec.end(), begin(result));
        return result;
    }

    template <class OT, class IT, class F>
    OT compre_f(IT &&range, F &&requirement)
    {
        vector<decltype(*begin(range))> vec;
        for (auto item : forward<IT>(range))
            if (requirement(item))
                vec.push_back(item);
        OT result(vec.size());
        copy(vec.begin(), vec.end(), begin(result));
        return result;
    }

    template <class OT, class IT>
    OT compre_c(IT &&range)
    {
        vector<decltype(*begin(range))> vec;
        for (auto item : forward<IT>(range))
            vec.push_back(item);
        OT result(vec.size());
        copy(vec.begin(), vec.end(), begin(result));
        return result;
    }
}