#include "atom.h"

namespace {
using position_t = Atom::position_t;
}

position_t &Atom::coordinate_vec() { return xyz_; }
position_t const &Atom::coordinate_vec() const { return xyz_; }

unsigned long Atom::atomic_number() const { return Z_; }

unsigned long charge(Atom const &a) { return a.atomic_number(); }
