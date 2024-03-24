#include "Matrix.h"
#include "string.h"
#include <new>

#define OUTOFBOUNDS 1

Matrix::Matrix(int m, int n) : m_m(m), m_n(n) {
	int i;
	m_tab=new Rational[m*n];
	m_lastErr=0;
}

Matrix::Matrix(int m, int n, Rational* val) : m_m(m), m_n(n) {
	int i;
	m_tab=new Rational[m*n];
	m_lastErr=0;
	for(i=0;i<m*n;i++) {
		m_tab[i]=val[i];
	}
}

Matrix::~Matrix() {
	delete[] m_tab;
}


ErrCode Matrix::getError() const {
	return m_lastErr;
}

ErrCode Matrix::popError() {
	ErrCode ret=m_lastErr;
	m_lastErr=0;
	return ret;
}

unsigned Matrix::getM() const {
	return m_m;
}

unsigned Matrix::getN() const {
	return m_n;
}

Rational Matrix::getVal(unsigned i, unsigned j) {
	if((i<m_m) && (j<m_n)) {
		return m_tab[i*m_n+m_m];
	} else {
		m_lastErr=OUTOFBOUNDS;
		return Rational();
	}
}

ErrCode Matrix::setVal(const Rational& x, unsigned i, unsigned j) {
	if((i<m_m) && (j<m_n)) {
		m_tab[i*m_n+m_m]=x;
		return 0;
	} else {
		m_lastErr=OUTOFBOUNDS;
		return OUTOFBOUNDS;
	}
}

char* Matrix::toString() const { // WIP
	unsigned* sizes=new (std::nothrow) unsigned[m_n];
	char** vals=new (std::nothrow) char*[m_m*m_n];
	unsigned len, sum=0;
	char* r=0;
	unsigned i, j, k, l;

	for(i=0;i<m_n;i++) {
		sizes[i]=0;
	}

	for(i=0;i<m_m*m_n;i++) {
		vals[i]=m_tab[i].toString();
		len=strlen(vals[i]);
		if(len>sizes[i%m_n]) {
			sizes[i%m_n]=len;
		}
		sum+=len;
	}

	len=0;
	for(i=0; i<m_n;i++) {
		len+=sizes[i];
	}

	r=new (std::nothrow) char[(2+3*(m_n-1)+len+3)
	                         *(2*m_m+1)];
	
	r[0]='+';
	r[1]='-';
	l=2;
	for(j=0;j<m_n-1;j++) {
		for(k=0; k<sizes[j]+2;k++){
			r[l]='-';
			l++;
		}
		r[l]='+';
		l++;
	}
	for(k=0; k<sizes[j]+2;k++){ // j=n-1
		r[l]='-';
		l++;
	}
	r[l]='+';
	r[l+1]='\n';
	l+=2;

	r[m_n*m_m-1]='\0';
	return r;

}

int Matrix::cmp(const Matrix& oth) const {
	int i;
	if((m_m!=oth.m_m) || (m_n!=oth.m_n)) {
		return 0;
	}
	for(i=0; i<m_m*m_n;i++) {
		if(m_tab[i]!=oth.m_tab[i]) {
			return 0;
		}
	}
	return 1;
}

Matrix* Matrix::operator  = (const Matrix& right) {
	m_n=right.m_n;
	m_m=right.m_m;
	if(m_tab) {
		delete[] m_tab;
	}
	m_tab=new Rational[m_m*m_n];
	(void)memcpy(m_tab, right.m_tab, m_m*m_n);
	return this;
}

Matrix* Matrix::operator += (const Matrix& right) {
	int i;
	if((m_n!=right.m_n) || (m_m!=right.m_m)) {
		m_lastErr=SIZE_ERROR;
		return this;
	}
	for(i=0;i<m_n*m_m;i++) {
		m_tab[i]+=right.m_tab[i];
	}
	return this;
}

Matrix* Matrix::operator -= (const Matrix& right) {
	int i;
	if((m_n!=right.m_n) || (m_m!=right.m_m)) {
		m_lastErr=SIZE_ERROR;
		return this;
	}
	for(i=0;i<m_n*m_m;i++) {
		m_tab[i]-=right.m_tab[i];
	}
	return this;
}

Matrix* Matrix::operator *= (const Matrix& right) {
	int i;
	if((m_n!=right.m_n) || (m_m!=right.m_m)) {
		m_lastErr=SIZE_ERROR;
		return this;
	}
	for(i=0;i<m_n*m_m;i++) {
		m_tab[i]*=right.m_tab[i];
	}
	return this;
}

Matrix* Matrix::operator /= (const Matrix& right) {
	int i;
	if((m_n!=right.m_n) || (m_m!=right.m_m)) {
		m_lastErr=SIZE_ERROR;
		return this;
	}
	for(i=0;i<m_n*m_m;i++) {
		m_tab[i]/=right.m_tab[i];
	}
	return this;
}

int operator == (const Matrix& left, const Matrix& right) {
	return left.cmp(right);
}
int operator != (const Matrix& left, const Matrix& right) {
	return !left.cmp(right);
}
