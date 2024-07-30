#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -Wno-unused-parameter -Wall
CC = g++

LIB = PGCD.o Rational.o
PROGRAMS = testRational testPGCD testMatrix testEchelon


.PHONY:	all clean

all: $(PROGRAMS)

clean:
	rm -f *.o *~ $(PROGRAMS)


PGCD.o: PGCD.c PGCD.h
	$(CC) $(GCC_FLAGS) -c PGCD.c

testPGCD: PGCD.o testPGCD.c
	$(CC)  $(CFLAGS) -g -o testPGCD PGCD.o testPGCD.c

Rational.o: Rational.cpp Rational.h
	$(CC) $(GCC_FLAGS) -c Rational.cpp

testRational: Rational.o PGCD.o testRational.c
	$(CC) $(CFLAGS) -g -o testRational Rational.o PGCD.o testRational.c

testMatrix: Matrix.h testMatrix.cpp
	$(CC) $(CFLAGS) -g -o testMatrix testMatrix.cpp

testEchelon: Matrix.h testEchelon.cpp
	$(CC) $(CFLAGS) -g -o testEchelon testEchelon.cpp
