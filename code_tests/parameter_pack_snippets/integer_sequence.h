#pragma once

#include <cstdlib>

/// seq and gen_seq are taken from stackoverflow's pretty print tuple answer.
template <std::size_t...>
struct integer_sequence {};

template <std::size_t N, std::size_t... Is>
struct gen_integer_sequence : gen_integer_sequence<N - 1, N - 1, Is...> {};

template <std::size_t... Is>
struct gen_integer_sequence<0, Is...> : integer_sequence<Is...> {};

