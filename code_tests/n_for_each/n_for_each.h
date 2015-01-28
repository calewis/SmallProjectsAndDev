#pragma once
#include <tuple>

template <typename Container1, typename Container2, typename Func1,
          typename Func2>
auto n_for_each(Container1 const &c1, Container2 const &c2, Func1 f1, Func2 f2)
    -> std::tuple<decltype(f1(c1.front(), c1.front())), decltype(f2(c2.front(), c2.front()))> {
    std::tuple<decltype(f1(c1.front(), c1.front())),
               decltype(f2(c2.front(), c2.front()))> vals;

    const auto end1 = c1.end();
    const auto end2 = c2.end();
    auto it2 = c2.begin();

    for (auto it1 = c1.begin(); it1 != end1; ++it1, ++it2) {
        auto &zero = std::get<0>(vals);
        auto &one = std::get<1>(vals);
        zero = f1(zero, *it1);
        one = f2(one, *it2);
    }

    return vals;
}
