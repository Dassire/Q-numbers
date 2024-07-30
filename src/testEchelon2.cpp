#include "Matrix.h"
#include "RationalMatrixUtils.h"
#include <stdio.h>

int main(int c, char** v) {
    int* tmp = new int[16] {1, 0, 4, 2, 1, 2, 6, 2, 2, 0, 8, 8, 2, 1, 10, 4};
	Matrix<Rational> M = create(4,4, tmp);
	Matrix<Rational> M3 = id(4);
	Matrix<Rational> M2 = M.echelon(&M3);
	printMatrix(M);
	printf("\n");
	printMatrix(M2);
	printf("\n");
	printMatrix(M3);
	printf("\n");
	printMatrix(M2 * M3);
    delete[] tmp;
	return 0;
}
