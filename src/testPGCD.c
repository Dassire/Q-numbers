#include <stdio.h>
#include <stdlib.h>

#include "PGCD.h"

int main(int argc, char** argv) {
	int a,b,u,v,r;
	if(argc<3) {
		fprintf(stderr, "Erreur");
		return 1;
	}

	a=atoi(argv[1]);
	b=atoi(argv[2]);

	r=PGCD(a,b,&u,&v);

	printf("%d=%d*%d+%d*%d\n", r,a,u,b,v);

	r=PGCD(a,b,&u,NULL);
	r=PGCD(a,b,NULL,&v);

	return 0;
}