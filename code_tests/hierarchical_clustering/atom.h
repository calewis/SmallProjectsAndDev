#pragma once

#include <array>

class Atom {
   public:
    using position_t = std::array<double, 3>;
    constexpr Atom() = default;
    Atom(Atom const &a) = default;
    Atom(Atom &&a) = default;
    Atom &operator=(Atom const &) = default;
    Atom &operator=(Atom &&) = default;

    Atom(position_t xyz, unsigned long Z) : xyz_(std::move(xyz)), Z_{Z} {}

    position_t &coordinate_vec();
    position_t const &coordinate_vec() const;

    unsigned long atomic_number() const;

   private:
    position_t xyz_ = {{0, 0, 0}};
    unsigned long Z_ = 0;
};

unsigned long charge(Atom const &a);
