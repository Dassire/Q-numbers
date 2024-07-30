#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include <string.h>
#include <stdlib.h>

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
					r[i * oth->getN() + j]+=oth->get(i,k)*get(k,j);
				}
			}
		}
		return r;
	}

	idx min_nonzero(idx i, idx j) const {
		idx r;
		r = i;
		// printf("j=%d\n", j);
		for(; i < m_m; i++) {
			// printf("(r=%d,j)=%d, (i=%d,j)=%d\n", r, get(r,j), i, get(i,j));
			if((get(r,j) == 0 && get(i,j) != 0) // get to the first non zero
					|| (get(i,j) != 0 && abs(get(i,j)) < abs(get(r,j)))) {
				r = i;
			}
		}
		return r;
	}

	void swap(idx i1, idx i2, T* buff) {
		bool desalloc = buff == NULL;
		if(desalloc) {
			buff = new T[m_n];
		}
		memcpy(buff, &(m_data[m_n * i1]), sizeof(T) * m_n);
		memcpy(&(m_data[m_n * i1]), &(m_data[m_n * i2]), sizeof(T) * m_n);
		memcpy(&(m_data[m_n * i2]), buff, sizeof(T) * m_n);
		if(desalloc) {
			delete[] buff;
		}
	}

public:
	Matrix(idx m, idx n, T* data) {
		m_m = m;
		m_n = n;
		m_data = data;
	}

	Matrix(idx m, idx n) {
		m_m=m;
		m_n=n;
		m_data=new T[m*n];
	}

	Matrix(const Matrix<T>& oth) {
		m_m = oth.getM();
		m_n = oth.getN();
		m_data = new T[m_m * m_n];
		memcpy(m_data, oth.m_data, sizeof(T) * m_m * m_n);
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
		Matrix<T> r(oth);
		int i;
		if(m_m == oth.getM() && m_n == oth.getN()) {
			for(i = 0; i < m_m * m_n; i++) {
				r.m_data[i] = m_data[i] + oth.m_data[i];
			}
			return r;
		} else {
			exit(1);
		}
	}

	Matrix<T> operator * (const Matrix<T>& oth) {
		T* dat;
		Matrix<T> r(oth);
		if(m_n == r.getM()) {
			dat = r.prod(this);
			delete[] r.m_data;
			r.m_m = m_n;
			r.m_data = dat;
			return r;
		} else {
			exit(1);
		}
	}

	
	void printMatrix() {
		int i,j;
		for(i = 0; i < getM(); i++) {
			for(j = 0; j < getN(); j++) {
				printf("%d\t", get(i,j));
			}
			printf("\n");
		}
	}
	

	Matrix<T> echelon(Matrix<T>* oth) const {
		Matrix<T> r(*this);
		T coef;
		T* buff = new T[oth && oth->getN() > m_n ? oth->getN() : m_n];
		int i,j,k;
		for(i=0; i < m_m - 1; i++) { // m_n ?
			k = r.min_nonzero(i, i);
			// printf("i = %d, k = %d\n", i, k);
			if(k!=i) {
				r.swap(i, k, buff);
				if(oth) {
					oth->swap(i, k, buff);
				}
			}
			if(r.get(i,i) == 0) continue;
			for(k=i + 1; k < m_m; k++) {
				coef = r.get(k,i)/r.get(i,i);
				for(j = i; j < m_n; j++) {
					r.set(k,j, r.get(k,j) - coef * r.get(i,j));
				}
				if(oth) {
					for(j = 0; j < oth->getN(); j++) {
						oth->set(k,j, oth->get(k,j) - coef * oth->get(i,j));
					}
				}
			}
			// r.printMatrix();
			// printf("\n");
		}
		printf("\n");
		delete[] buff;
		return r;
	}
};

#endif
