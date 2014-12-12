CFLAGS=-Wall -Wextra -g -O3 -I. --std=c11

all: libprime.a test

test: test.o prime.o

libprime.a: prime.o
	ar r libprime.a prime.o

clean:	
	rm -rf *.o *.a
