#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -Wno-unused-parameter -Wall -g
CC = g++

LIB = PGCD.o Rational.o IntMatrixUtils.o RationalMatrixUtils.o
PROGRAMS = testRational testPGCD testMatrix testEchelon testEchelon2


.PHONY:	all clean

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)


PGCD.o: PGCD.c PGCD.h
	$(CC) $(CFLAGS) -c PGCD.c

Rational.o: Rational.cpp Rational.h
	$(CC) $(CFLAGS) -c Rational.cpp

IntMatrixUtils.o: IntMatrixUtils.cpp IntMatrixUtils.h
	$(CC) $(CFLAGS) -c IntMatrixUtils.cpp

RationalMatrixUtils.o: RationalMatrixUtils.cpp RationalMatrixUtils.h
	$(CC) $(CFLAGS) -c RationalMatrixUtils.cpp

testPGCD: PGCD.o testPGCD.c
	$(CC)  $(CFLAGS) -o testPGCD PGCD.o testPGCD.c

testRational: Rational.o PGCD.o testRational.c
	$(CC) $(CFLAGS)  -o testRational Rational.o PGCD.o testRational.c

testMatrix: Matrix.h testMatrix.cpp
	$(CC) $(CFLAGS) -o testMatrix testMatrix.cpp

testEchelon: testEchelon.cpp Matrix.h IntMatrixUtils.o
	$(CC) $(CFLAGS) -o testEchelon testEchelon.cpp IntMatrixUtils.o

testEchelon2: testEchelon2.cpp Matrix.h RationalMatrixUtils.o Rational.o PGCD.o
	$(CC) $(CFLAGS) -o testEchelon2 testEchelon2.cpp RationalMatrixUtils.o Rational.o PGCD.o
