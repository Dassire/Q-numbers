#ifndef RATIONALMATRIXUTILS_H_
#define RATIONALMATRIXUTILS_H_

#include "Rational.h"
#include "Matrix.h"

void printMatrix(const Matrix<Rational>& M);

Matrix<Rational> id(idx n);

Matrix<Rational> create(idx m, idx n, int* dat);

#endif