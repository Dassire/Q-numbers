#ifndef MATRIX_H_
#define MATRIX_H_

/*
#include <string>

#include "Dim2Array.h"

class Matric : Dim2Array<int>
*/

#include <string>
#include <string.h>

typedef int idx;

template <class T>
class Matrix {
    private:
    idx m_m;
    idx m_n;
    T* m_data;

    T* prod(const Matrix<T>* oth) const {
        int i,j,k;
        T* r = new T[oth->getM() * m_n];
        for(i = 0; i < oth->getM(); i++) {
            for(j = 0; j < m_n; j++) {
                r[i * oth->getM() + j]=0;
                for(k=0;k<m_m;k++) {
                    r[i * oth->getM() + j]+=oth->get(i,k)*get(k,j);
                }
            }
        }
        return r;
    }

public:
    Matrix(idx m, idx n) {
        m_m=m;
        m_n=n;
        m_data=new T[m*n];
    }

    Matrix(idx m, idx n, T* data) {
        m_m = m;
        m_n = n;
        m_data = data;
    }

    ~Matrix() {
        delete[] m_data;
    }

    T get(idx i, idx j) const {
        if (i<m_m && j<m_n) {
            return m_data[i * m_n + j];
        } else {
            exit(1);
        }
    }

    idx getM() const { return m_m; }
    idx getN() const { return m_n; }

    Matrix<T>& set(idx i, idx j, T val) {
        m_data[i * m_n + j] = val;
        return *this;
    }

	Matrix<T>& operator = (const Matrix<T>& oth) {
		int nsize = oth.getM() * oth.getN();
		if(m_m * m_n != nsize) {
			delete[] m_data;
			m_data = new T[nsize];
		}
		memcpy(m_data, oth.m_data, sizeof(T) * nsize);
		m_m = oth.getM();
		m_n = oth.getN();
		return *this;
	}

    Matrix<T>& operator += (const Matrix<T>& oth) {
        int i;
        if(m_m == oth.getM() && m_n == oth.getN()) {
            for(i=0; i<m_m * m_n; i++) {
                idx tmp = oth.m_data[i];
                m_data[i]+=tmp;
            }
        } else {
            exit(1);
        }
        return *this;
    }

    Matrix<T>& operator -= (const Matrix<T>& oth) {
        int i;
        if(m_m == oth.getM() && m_n == oth.getN()) {
            for(i=0; i<m_m * m_n; i++) {
                m_data[i]-=oth.m_data[i];
            }
        } else {
            exit(1);
        }
        return *this;
    }

    Matrix<T>& operator *= (const Matrix<T>& oth) {
        T* tmp;
        if(m_n == oth.getM()) {
            tmp = oth.prod(this);
            delete[] m_data;
            m_data = tmp;
            m_n = oth.getN();
        } else {
            exit(1);
        }
        return *this;
    }

	Matrix<T> operator + (const Matrix<T>& oth) {
		T* dat;
		Matrix<T> r(oth);
		int i;
		if(m_m == oth.getM() && m_n == oth.getN()) {
			dat = new T[m_m * m_n];
			for(i = 0; i < m_m * m_n; i++) {
				dat[i] = m_data[i] + oth.m_data[i];
			}
			r.m_data = dat;
			return r;
		} else {
			exit(1);
		}
	}

    Matrix<T> operator * (const Matrix<T>& oth) {
        T* dat;
		Matrix<T> r(oth);
        if(m_n == oth.getM()) {
            dat = r.prod(this);
            r.m_m = m_n;
            r.m_data = dat;
            return r;
        } else {
            exit(1);
        }
    }
};

/*
Matrix<T> operator + (const Matrix<T>& l, const Matrix<T>& r) {
    idx i=0;
    T* data = new T[m_n]{ ([](idx* i){l->}) };
    return 0;
}
*/

#endif