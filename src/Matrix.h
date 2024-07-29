#ifndef MATRIX_H_
#define MATRIX_H_

/*
#include <string>

#include "Dim2Array.h"

class Matric : Dim2Array<int>
*/

#include <string>

typedef int index;

template <class T>
class Matrix {
    private:
    index m_m;
    index m_n;
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
    Matrix(index m, index n) {
        m_m=m;
        m_n=n;
        m_data=new T[m*n];
    }

    Matrix(index m, index n, T* data) {
        m_m = m;
        m_n = n;
        m_data = data;
    }

    ~Matrix() {
        delete[] m_data;
    }

    T get(index i, index j) const {
        if (i<m_m && j<m_n) {
            return m_data[i * m_n + j];
        } else {
            exit(1);
        }
    }

    index getM() const { return m_m; }
    index getN() const { return m_n; }

    Matrix<T>& set(index i, index j, T val) {
        m_data[i * m_n + j] = val;
        return *this;
    }

    Matrix<T>& operator += (const Matrix<T>& oth) {
        int i;
        if(m_m == oth.getM() && m_n == oth.getN()) {
            for(i=0; i<m_m * m_n; i++) {
                index tmp = oth.m_data[i];
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
    index i=0;
    T* data = new T[m_n]{ ([](index* i){l->}) };
    return 0;
}
*/

#endif