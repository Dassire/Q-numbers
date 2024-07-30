#include "Matrix.h"
#include "IntMatrixUtils.h"
#include <stdio.h>

int main(int c, char** v) {
	Matrix<int> M(4,4, new int[16] {1, 0, 4, 2, 1, 2, 6, 2, 2, 0, 8, 8, 2, 1, 10, 4});
	Matrix<int> M3 = id(4);
	Matrix<int> M2 = M.echelon(0);
	printMatrix(M);
	printf("\n");
	printMatrix(M2);
	printf("\n");
	printMatrix(M3);
	printf("\n");
	printMatrix(M2 * M3);
	return 0;
}
