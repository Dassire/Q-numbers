#include "IntMatrixUtils.h"
#include <stdio.h>

void printMatrix(const Matrix<int>& M) {
	int i,j;
	for(i = 0; i < M.getM(); i++) {
		for(j = 0; j < M.getN(); j++) {
			printf("%d\t", M.get(i,j));
		}
		printf("\n");
	}
}

Matrix<int> id(idx n) {
    Matrix<int> r(n,n, new int[n * n]());
    int i;
    for(i = 0; i < n; i++) {
        r.set(i,i,1);
    }
    return r;
}
