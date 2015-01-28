#include "capture_types.h"
#include "integer_sequence.h"
#include "last_type.h"

#include <string>
#include <typeinfo>
#include <iostream>

class X {};

template <typename... Args, std::size_t... Is>
auto func_helper(std::tuple<Args...> const &t, integer_sequence<Is...>)
    -> std::tuple<typename type_list<Args...>::template type<Is>...> {
    return std::tuple<typename type_list<Args...>::template type<Is>...>{
        std::get<Is>(t)...};
}

template <typename... Args>
void func(Args... args) {
    constexpr std::size_t first_N = sizeof...(Args)-1;
    auto t = func_helper(std::forward_as_tuple(args...),
                         gen_integer_sequence<first_N>{});
    std::cout << "Type of tuple we created is " 
              << typeid(t).name() << std::endl;

    constexpr auto tuple_last = std::tuple_size<decltype(t)>::value - 1;
    std::cout << "Type of last element in tuple is " 
              << typeid(std::get<tuple_last>(t)).name() << std::endl;
}

int main() {
    func(std::string{"Hi"}, 0, 0ul, 0.0, X{}, 0.0f);
    return 0;
}
