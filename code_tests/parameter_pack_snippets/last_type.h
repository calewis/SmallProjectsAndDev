// Code to get the last type out of a parameter pack, will require looping
// over all other types in the pack.

#pragma once

template <typename First, typename... Rest>
class last_type : public last_type<Rest...> {};

template <typename Last>
class last_type<Last> {
   public:
    using Type = Last;
};
