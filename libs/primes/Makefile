CFLAGS=-Wall -Wextra -g -O3

all: libprime.a

libprime.a: prime.o
	ar r libprime.a prime.o

clean:	
	rm -rf *.o *.a
