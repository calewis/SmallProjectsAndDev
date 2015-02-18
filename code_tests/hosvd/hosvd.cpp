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

template <typename... Args>
TiledArray::Range make_range(Args... args) {
    return TiledArray::Range(args...);
}

Tensor vectors(Tensor const &a) {
    auto const &size = a.range().size();
    Eigen::Map<const Matrix> map(a.data(), size[0], size[1] * size[2]);

    Eigen::JacobiSVD<Matrix> svd(map,
                                 Eigen::ComputeThinU | Eigen::ComputeThinV);
    auto const &vals = svd.singularValues();

    auto rank = 0;
    for (auto i = 0; i < vals.size(); ++i) {
        if (1e-12 < vals[i]) {
            ++rank;
        }
    }

    auto matrixU = svd.matrixU().leftCols(rank);
    Tensor U{Range(matrixU.rows(), matrixU.cols())};

    for (auto i = 0; i < matrixU.size(); ++i) {
        U[i] = *(matrixU.data() + i);
    }

    return U;
}

Tensor Kron(Tensor const &a, Tensor const &b) {
    auto const &asize = a.range().size();
    auto const &bsize = b.range().size();
    const auto ab0 = asize[0] * bsize[0];
    const auto ab1 = asize[1] * bsize[1];

    Tensor out(Range(ab0, ab1));

    Eigen::Map<Matrix> outm(out.data(), ab0, ab1);
    Eigen::Map<const Matrix> am(a.data(), asize[0], asize[1]);
    Eigen::Map<const Matrix> bm(b.data(), bsize[0], bsize[1]);

    outm = Matrix::Zero(ab0, ab1);
    std::cout << "outm = \n" << outm << std::endl;

    auto row_start = 0;
    for (auto i = 0; i < am.rows(); ++i) {
        auto col_start = 0;
        for (auto j = 0; j < am.cols(); ++j) {
            outm.block(row_start, col_start, bsize[0], bsize[1]) = am(i, j) * bm;
            col_start += bsize[1];
        }
        row_start += bsize[0];
        std::cout << "outm = \n" << std::endl;
    }

    return out;
}

Tensor FormS(Tensor const &U1, Tensor const &A, Tensor const &K) {
    auto const &usize = U1.range().size();
    auto const &asize = A.range().size();
    auto const &ksize = K.range().size();
    Eigen::Map<const Matrix> um(U1.data(), usize[0], usize[1]);
    Eigen::Map<const Matrix> am(A.data(), asize[0], asize[1] * asize[2]);
    Eigen::Map<const Matrix> km(K.data(), ksize[0], ksize[1]);

    Matrix outtemp(usize[1], asize[1] * asize[2]);
    outtemp = um.transpose() * am;

    Tensor out{Range(usize[1], asize[1], asize[2])};
    Eigen::Map<Matrix> outm(out.data(), usize[1], asize[1] * asize[2]);
    outm = outtemp * km;
    return out;
}

Tensor FormA(Tensor const &U1, Tensor const &S, Tensor const &K) {
    auto const &usize = U1.range().size();
    auto const &ssize = S.range().size();
    auto const &ksize = K.range().size();
    Eigen::Map<const Matrix> um(U1.data(), usize[0], usize[1]);
    Eigen::Map<const Matrix> sm(S.data(), ssize[0], ssize[1] * ssize[2]);
    Eigen::Map<const Matrix> km(K.data(), ksize[0], ksize[1]);

    Matrix outtemp(usize[0], ssize[1] * ssize[2]);
    outtemp = um * sm;
    std::cout << outtemp << std::endl;

    Tensor out{Range(usize[0], ssize[1], ssize[2])};
    Eigen::Map<Matrix> outm(out.data(), usize[0], ssize[1] * ssize[2]);
    outm = outtemp * km.transpose();
    return out;
}

int main(int argc, char **argv) {
    auto tensor = Tensor{make_range(3, 2, 2)};
    for (auto i = 1; i <= 12; ++i) {
        tensor[i - 1] = i;
    }
    auto u1 = vectors(tensor);
    auto u2 = vectors(Tensor{tensor, Perm{1, 0, 2}});
    auto u3 = vectors(Tensor{tensor, Perm{2, 1, 0}});

    std::cout << tensor << std::endl;
    std::cout << u1 << std::endl;
    std::cout << u2 << std::endl;
    std::cout << u3 << std::endl;

    auto K = Kron(u3,u2);
    std::cout << "K = \n" << K << std::endl;
    auto S = FormS(u1, tensor, K);
    std::cout << "S = \n" << S << std::endl;
    auto Tapprox = FormA(u1, S, K);
    std::cout << "Aapprox = \n" << Tapprox << std::endl;

    return 0;
}
