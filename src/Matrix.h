#ifndef MATRIX_H_
#define MATRIX_H_

#include <string>
#include <string.h>
#include <stdlib.h>

typedef int idx;

template <class T>
T* array_copy(T* dest, T* src, idx size) {
	int i;
	for(i = 0; i < size ; i++) {
		dest[i] = src[i];
	}
	return dest;
}

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
		array_copy(buff, &(m_data[m_n * i1]), m_n);
		array_copy(&(m_data[m_n * i1]), &(m_data[m_n * i2]), m_n);
		array_copy(&(m_data[m_n * i2]), buff, m_n);
		if(desalloc) {
			delete[] buff;
		}
	}


	void Rprint() {
		int i,j;
		char* str;
		for(i = 0; i < m_m; i++) {
			for(j = 0; j < m_n; j++) {
				str = get(i,j).simplify().toString();
				printf("%s\t", str);
				delete[] str;
			}
			printf("\n");
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
		array_copy(m_data, oth.m_data, m_m * m_n);
	}

	~Matrix() {
		delete[] m_data;
	}

	T get(idx i, idx j) const {
		if (i<m_m && j<m_n) {
			return m_data[i * m_n + j];
		} else {
			fprintf(stderr, "get error : %d < %d or %d < %d\n", i, m_m, j, m_n);
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
		array_copy(m_data, oth.m_data, nsize);
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
			fprintf(stderr, "Matrix addition assign error");
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
			fprintf(stderr, "Matrix sub assign error");
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
			fprintf(stderr, "Matrix product assign error");
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
			fprintf(stderr, "Matrix addition error");
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
			fprintf(stderr, "Matrix product error");
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
		int i,j,k; // add a counter for the col with non null
		idx l;
		for(i=0, l = 0; (i < (m_m - 1)) && (l < m_n); i++, l++) { // m_n ?
			// Get to the first column without 0s
			do {
				k = i;
				while(k < m_m && r.get(k,l) == 0) k++;
				if(k >= m_m || r.get(k,l) == 0) l++;
			} while(l < m_n && ((k < m_m && r.get(k,l) == 0) || !(k < m_m)));
			if(l >= m_n) break; // only 0s
			// maybe merge
			k = r.min_nonzero(i, l);
			// printf("i = %d, k = %d\n", i, k);
			if(k!=i) {
				r.swap(i, k, buff);
				if(oth) {
					oth->swap(i, k, buff);
				}
			}
			if(r.get(i,l) == 0) continue;
			for(k=i + 1; k < m_m; k++) {
				j = l;
				/* while(j < r.getN() && r.get(i,j) != 0) j++; */
				coef = r.get(k,l)/r.get(i,l);
				for(; j < m_n; j++) {
					r.set(k,j, r.get(k,j) - coef * r.get(i,j));
				}
				if(oth) {
					for(j = 0; j < oth->getN(); j++) {
						oth->set(k,j, oth->get(k,j) - coef * oth->get(i,j));
					}
				}
			}
			// printf("%d,%d\n", i, l);
			// r.printMatrix();
			// printf("\n");
		}
		// printf("\n");
		delete[] buff;
		return r;
	}

	Matrix<T> gaussian_elimination(Matrix<T>* oth) {
		Matrix<T> r=echelon(oth);
		T zero, one;
		int i,j,k,l;
		zero = 0;
		one = 1;
		/*
		r.Rprint();
		if(oth) {
			printf("\n");
			oth->Rprint();
		}
		printf("\n\n");
		 */
		for(i = r.getM() - 1; i >= 0; i --) {
			j = i;
			while(j < r.getN() && r.get(i,j) == 0) j++;
			// fprintf(stderr, "%d < %d\n", j, r.getN());
			if(j >= r.getN()) continue;
			// fprintf(stderr, "%d < %d : true && %s != 0\n", j, r.getN(), r.get(i,j).toString());
			// printf("line\n");

			// Divide the line
			for(l = j + 1; l < r.getN(); l++) {
				// fprintf(stderr, "1 : %d/%d\n", r.get(i,j).numerator(),r.get(i,j).numerator());
				// fprintf(stderr, "%s\n", r.get(i,l).toString());
				r.set(i,l, r.get(i,l) / r.get(i,j));
				// fprintf(stderr, "%s\n", r.get(i,l).toString());
			}
			// r.Rprint();
			// printf("\n");
			if(oth) {
				for(l = 0; l < oth->getN(); l++) {
					// fprintf(stderr, "2 : %d/%d\n", r.get(i,j).numerator(),r.get(i,j).numerator());
					oth->set(i,l, oth->get(i,l) / r.get(i,j));
					// r.Rprint();
					// printf("\n");
				}
			}
			// oth->Rprint(); printf("\n\n");

			for(k = 0; k < i; k++) {
				// coef = r.get(k,j) / r.get(i,j);
				for(l = j + 1; l < r.getN(); l++) {
					// printf("%d,%d : %s - (%s * %s) = %s\n", k, l, r.get(k,l).toString(), r.get(i,l).toString(), r.get(k,j).toString(), (r.get(k,l) - (r.get(il) * r.get(k,j))).toString());
					r.set(k,l, r.get(k,l) - (r.get(i,l) * r.get(k,j)));
				}
				if(oth) {
					for(l = 0; l < oth->getN(); l++) {
						// printf("%d,%d : %s - (%s * %s) = %s\n", k, l, oth->get(k,l).toString(), oth->get(i,l).toString(), r.get(k,j).toString(), (oth->get(k,l) - (oth->get(i,l) * r.get(k,j))).toString());
						oth->set(k,l, oth->get(k,l) - (oth->get(i,l) * r.get(k,j)));
						// oth->Rprint(); printf("\n");
					}
				}
				r.set(k,j, zero);
			}
			// fprintf(stderr, "3 : %d/%d\n", r.get(i,j).numerator(),r.get(i,j).numerator());
			r.set(i,j, one);
			/*
			r.Rprint();
			if(oth) {
				printf("\n");
				oth->Rprint();
			}
			printf("\n\n");
			 */
		}
		return r;
	}
};

#endif
