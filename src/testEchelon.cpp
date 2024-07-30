#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

void printMatrix(const Matrix<int>& M) {
    int i,j;
    for(i = 0; i < M.getM(); i++) {
        for(j = 0; j < M.getN(); j++) {
            printf("%d\t", M.get(i,j));
        }
        printf("\n");
    }
}

int main(int c, char** v) {
    Matrix<int> M(4,4, new int[16] {1, 0, 4, 2, 1, 2, 6, 2, 2, 0, 8, 8, 2, 1, 9, 4});
    Matrix<int> M2 = M.echelon(0);
    printMatrix(M);
    printf("\n");
    printMatrix(M2);
    return 0;
}
