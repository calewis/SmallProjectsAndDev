#include "common.h"
#include "fake_density.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(int argc, char **argv) {
    unsigned int dim = (argc >= 2) ? std::stoul(argv[1]) : 4;
    unsigned int occ = (argc >= 3) ? std::stoul(argv[2]) : 1;

    auto D = fake_density(dim, occ);

    if (dim < 5) {
        std::cout << "D = \n" << D << std::endl;
    }

    eig::JacobiSVD<Matrix> svd(D);
    std::cout << "Singular values = \n" << svd.singularValues().transpose()
              << std::endl;

    auto max_pos = [](Matrix const &m) {
        auto max_pos = std::make_pair(0, 0);
        auto max_elem = std::abs(m(0, 0));
        for (auto i = 1; i < m.rows(); ++i) {
            for (auto j = 0; j < m.cols(); ++j) {
                if (max_elem < std::abs(m(i, j))) {
                    max_pos = std::make_pair(i, j);
                    max_elem = std::abs(m(i, j));
                }
            }
        }

        return max_pos;
    };

    Matrix Rp = D;
    Matrix S = Matrix::Zero(dim, dim);
    Matrix L = Matrix::Zero(dim, occ);
    Matrix R = Matrix::Zero(occ, dim);

    // Fully pivoted ACA
    for (auto i = 0ul; i < occ; ++i) {
        auto pivot = max_pos(Rp);
        auto gamma = 1.0/Rp(pivot.first, pivot.second);

        eig::VectorXd c = gamma * Rp.col(pivot.second);
        eig::VectorXd r = Rp.row(pivot.first);

        L.col(i) = c;
        R.row(i) = r;

        Rp = Rp - c * r.transpose();
        S = S + c * r.transpose();

        std::cout << "Diff norm = " << (D - S).lpNorm<2>() << std::endl;
    }
    
    std::cout << "Diff norm = " << (D - L * R).lpNorm<2>() << std::endl;

    std::cout << "L = \n" << L << std::endl;
    std::cout << "R = \n" << R << std::endl;

    return 0;
}
