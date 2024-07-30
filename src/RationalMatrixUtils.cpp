#include "RationalMatrixUtils.h"

void printMatrix(const Matrix<Rational>& M) {
	int i,j;
    char* str;
	for(i = 0; i < M.getM(); i++) {
		for(j = 0; j < M.getN(); j++) {
            str = M.get(i,j).simplify().toString();
			printf("%s\t", str);
            delete[] str;
		}
		printf("\n");
	}
}

Matrix<Rational> id(idx n) {
    Matrix<Rational> r(n,n, new Rational[n * n]());
    Rational one(1,1);
    int i;
    for(i = 0; i < n; i++) {
        r.set(i,i,one);
    }
    return r;
}

Matrix<Rational> create(idx m, idx n, int* dat) {
    int i;
    Rational* ndat = new Rational[m * n];
    for(i = 0; i < (m * n); i++) {
        Rational x(dat[i], 1);
        ndat[i] = x;
    }
    Matrix<Rational> r(m, n, ndat);
    return r;
}
