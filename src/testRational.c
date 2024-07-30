#include "Rational.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	Rational x1(5,2);
	Rational x2(7,-2);
	Rational x3=x1+x2;
	char* str;

	str=x1.toString();
	printf("%s\n", str);
	delete[] str;
	str=x2.toString();
	printf("%s\n", str);
	delete[] str;
	str=x3.toString();
	printf("%s\n", str);
	delete[] str;
	x3.simplify();
	str=x3.toString();
	printf("%s\n", str);
	delete[] str;
	str=(x3 - x1 * x2).toString();
	printf("%s\n", str);
	delete[] str;
	str=(x3 - x1 * x2).simplify().toString();
	printf("%s\n", str);
	delete[] str;
	printf("%d\n", x2.cmp(x1));
	return 0;
}