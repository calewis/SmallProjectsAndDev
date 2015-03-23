#pragma once

#include <Eigen/Dense>

namespace eig = Eigen;

using Matrix = eig::Matrix<double, eig::Dynamic, eig::Dynamic, eig::RowMajor>;
