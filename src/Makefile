#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -Wno-unused-parameter -Wall
CC = g++

LIB = PGCD.o Rational.o
PROGRAMS = testRational testPGCD testMatrix


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

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(GCC_FLAGS) -c Matrix.cpp

testMatrix: Matrix.o Rational.o PGCD.o testMatrix.c
	$(CC) $(CFLAGS) -g -o testMatrix Matrix.o Rational.o PGCD.o testMatrix.c
