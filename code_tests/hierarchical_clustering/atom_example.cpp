#include "atom.h"
#include <array>
#include <iostream>

int main() {
    std::cout << "Please enter a charge for the atom." << std::endl;
    double Z = 0.0;
    std::cin >> Z;
    std::array<double, 3> pos = {{0, 0, 0}};
    Atom a(pos, Z);

    std::cout << "The Atoms charge is " << charge(a) << std::endl;

    return 0;
}
