// Code which will allow for the capture of types in a tuple and the expansion
// of those types into a template declaration
#pragma once

#include <tuple>

// code taken from and inspired by
// http://en.cppreference.com/w/cpp/utility/tuple/tuple_element

template <class... Args>
class type_list {
   public:
    template <std::size_t N>
    using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
};


