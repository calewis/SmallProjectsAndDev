#pragma once

#include "common.h"

Matrix fake_density(unsigned int nrows, unsigned int occupation) {
    Matrix init = Matrix::Random(nrows, occupation);
    eig::ColPivHouseholderQR<Matrix> qr(init);
    Matrix Q = Matrix(qr.matrixQ()).leftCols(occupation);
    return Q * Q.transpose();
}
