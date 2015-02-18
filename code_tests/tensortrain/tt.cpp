#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <array>
#include "/Users/drewlewis/software/install/tiledarray/sparse_new_summa_debug/include/tiledarray.h"

using Tensor = TiledArray::Tensor<double>;
using Perm = TiledArray::Permutation;
using Range = TiledArray::Range;
using Matrix =
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

int main(int argc, char **argv) {
    auto tensor = Tensor{Range(3, 2, 2)};
    for (auto i = 1; i <= 12; ++i) {
        tensor[i - 1] = i;
    }

    auto const &tsize = tensor.range().size();
    Eigen::Map<Matrix> tmap(tensor.data(), tsize[0], tsize[1] * tsize[2]);
    Eigen::JacobiSVD<Matrix> svd(tmap,
                                 Eigen::ComputeThinU | Eigen::ComputeThinV);
    auto const &vals = svd.singularValues();
    auto rank = 0;
    for (auto i = 0; i < vals.size(); ++i) {
        if (vals[i] > 1e-10) {
            ++rank;
        }
    }
    Matrix mU = svd.matrixU().leftCols(rank);
    Matrix dV = svd.singularValues().asDiagonal();
    Matrix v = dV.block(0,0,rank, rank) * svd.matrixV().transpose().topRows(rank);

    std::cout << "U = \n" << mU << std::endl;
    std::cout << "v = \n" << v << std::endl;
    std::cout << "Approx = \n" << mU * v << std::endl;

    // Resize to 4*2
    v.resize(4,2);
    svd.compute(v, Eigen::ComputeThinU | Eigen::ComputeThinV);
    auto const &vals2 = svd.singularValues();
    rank = 0;
    for (auto i = 0; i < vals2.size(); ++i) {
        if (vals2[i] > 1e-10) {
            ++rank;
        }
    }
    Matrix mU2 = svd.matrixU().leftCols(rank);
    Matrix dV2 = svd.singularValues().asDiagonal();
    Matrix v2 = dV.block(0,0,rank, rank) * svd.matrixV().transpose().topRows(rank);

    std::cout << "U2 = \n" << mU2 << std::endl;
    std::cout << "v2 = \n" << v2 << std::endl;

    mU2.resize(2,4);
    Matrix Ucombo = mU * mU2;

    Ucombo.resize(6,2);
    std::cout << "Ucombo = \n" << Ucombo << std::endl;
    
    svd.compute(Ucombo, Eigen::ComputeThinU | Eigen::ComputeThinV);
    auto const &vals3 = svd.singularValues();
    rank = 0;
    for (auto i = 0; i < vals2.size(); ++i) {
        if (vals3[i] > 1e-10) {
            ++rank;
        }
    }
    Matrix mU3 = svd.matrixU().leftCols(rank);
    Matrix dV3 = svd.singularValues().asDiagonal();
    Matrix v3 = dV.block(0,0,rank, rank) * svd.matrixV().transpose().topRows(rank);

    std::cout << "U3 = \n" << mU3 << std::endl;
    std::cout << "v3 = \n" << v3 << std::endl;

    return 0;
}
