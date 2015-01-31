#include "clusterable.h"
#include "atom.h"
#include "cluster.h"

#include <iostream>

int main() {
    std::array<double, 3> pos = {{0, 0, 1}};
    Atom a_1(pos, 3);
    Atom a_2(pos, 4);

    std::cout << "\nCharge of a_1 = " << charge(a_1) << std::endl;
    std::cout << "Charge of a_2 = " << charge(a_2) << std::endl;

    Clusterable ca_1(std::move(a_1));
    Clusterable ca_2(std::move(a_2));

    std::cout << "\nCharge of clusterable 1 = " << charge(ca_1) << std::endl;

    Cluster cl_1({ca_1, ca_2});
    std::cout << "\nCharge of cluster 1 = " << charge(cl_1) << std::endl;

    Clusterable ca_3(std::move(cl_1));
    std::cout << "\nCharge of Clusterable wrapping a cluster = " << charge(ca_3)
              << std::endl;

    Clusterable ca_4(Atom(pos, 5));

    Cluster cl_2({ca_3, ca_4});
    std::cout << "\nCharge of Cluster containing 1 sub cluster and 1 atom = "
              << charge(cl_2) << std::endl;

    return 0;
}
