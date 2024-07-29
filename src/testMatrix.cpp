#include "Matrix.h"
#include <stdio.h>

int main (int c, char** v) {
    int* dat = new int[4]{1, 2, 3, 4};
    Matrix<int> M(2,2,dat);
    for(int i = 0; i < M.getM(); i++) {
        for(int j = 0; j < M.getN(); j++) {
            printf("%d,%d : %d\n", i,j, M.get(i,j));
        }
    }
    printf("\n");
    M+=M;
    for(int i = 0; i < M.getM(); i++) {
        for(int j = 0; j < M.getN(); j++) {
            printf("%d,%d : %d\n", i,j, M.get(i,j));
        }
    }
    printf("\n");
    Matrix<int> N =
    M * M;
    for(int i = 0; i < N.getM(); i++) {
        for(int j = 0; j < N.getN(); j++) {
            printf("%d,%d : %d\n", i,j, N.get(i,j));
        }
    }
    printf("\n");
    M*=N;
    for(int i = 0; i < M.getM(); i++) {
        for(int j = 0; j < M.getN(); j++) {
            printf("%d,%d : %d\n", i,j, M.get(i,j));
        }
    }
    printf("\n");
    M-=M;
    for(int i = 0; i < M.getM(); i++) {
        for(int j = 0; j < M.getN(); j++) {
            printf("%d,%d : %d\n", i,j, M.get(i,j));
        }
    }
    printf("\n");
    return 0;
}