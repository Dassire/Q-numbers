#ifndef MATRIX_X
#define MATRIX_X

#include "Rational.h"

typedef int ErrCode;
#define SIZE_ERROR 1
#define ALLOC_ERROR 2;

class Matrix {
private:
	Rational* m_tab;
	unsigned m_m, m_n;
	ErrCode m_lastErr;

public:
	Matrix(int m, int n);
	Matrix(int m, int n, Rational* val);
	~Matrix();

	ErrCode getError() const;
	ErrCode popError();

	unsigned getM() const;
	unsigned getN() const;
	Rational getVal(unsigned i, unsigned j);
	ErrCode setVal(const Rational&, unsigned i, unsigned j);
	char* toString() const;

	int cmp(const Matrix&) const;

	Matrix* operator  = (const Matrix&);
	Matrix* operator += (const Matrix&);
	Matrix* operator -= (const Matrix&);
	Matrix* operator *= (const Matrix&);
	Matrix* operator /= (const Matrix&);
};

/*
Matrix operator + (const Matrix&, const Matrix&);
Matrix operator - (const Matrix&, const Matrix&);
Matrix operator * (const Matrix&, const Matrix&);
Matrix operator / (const Matrix&, const Matrix&);
*/

int operator == (const Matrix&, const Matrix&);
int operator != (const Matrix&, const Matrix&);


#endif