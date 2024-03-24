#include "PGCD.h"
#include "stdlib.h"

int PGCD(int a, int b, int* u, int* v) {
	int uNew;
	int vNew;
	int condCoef=(u!=NULL) && (v!=NULL);
	int q;
	int tmp;

	if(condCoef) {
		*u=1;
		*v=0;
		uNew=0;
		vNew=1;
	}

	while(b!=0) {
		q=a/b;

		tmp=a;
		a=b;
		b=tmp-(q*b);

		if(condCoef) {
			tmp=*u;
			*u=uNew;
			uNew=tmp-(q*uNew);

			tmp=*v;
			*v=vNew;
			vNew=tmp-(q*vNew);
		}
	}
	return a;
}

