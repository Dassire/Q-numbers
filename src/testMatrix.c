#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <new>

int main(int argc, char const *argv[]) {
	Rational* tab;
	try {
		tab=new Rational[4];
	} catch(std::bad_alloc& e) {
		fprintf(stderr, "%s\n", e.what());
		exit(1);
	}
	printf("hello\n");
	unsigned i,j;
	tab[0]=Rational(5,2);
	tab[1]=Rational(7,-2);
	tab[2]=tab[0]+tab[1];
	tab[3]=tab[0]-tab[1];
	char* str;
	// printf("hello %d %d\n", m_m, m_n);

	Matrix M(2,2,tab);

	for(i=0;i<M.getM();i++) {
		for(j=0;j<M.getN();j++) {
			str=M.getVal(i,j).toString();
			printf("%s\t", str);
			delete str;
		}
		printf("\n");
	}

	return 0;
}