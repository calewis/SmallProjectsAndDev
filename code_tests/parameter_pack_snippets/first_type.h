// Code to get the first type out of a parameter pack
#pragma once

template <typename First, typename... Rest>
class first_type {
   public:
    using Type = First;
};
