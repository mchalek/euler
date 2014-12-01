#include <prime.h>
#include <stdio.h>
#include <stdlib.h>

long cube(long x, long m)
{
    long xmod = x % m;
    long x3 = xmod*xmod*xmod;

    return x3 % m;
}

#define MAX_X 15156
#define MAX_P 1865706

int main()
{
    long np;
    long *p;

    primes(MAX_P, &p, &np);

    // look for values x^3 - 1 == np, for p <= 1865706
    // note: x^3 == 1 mod p => (x^2)^3 == 1 mod p so we only have to find
    // the first solution, so n <= p
    // => check x up to (1865706)^(2/3) == 15156

    long i;
    for(i = 0; i <= MAX_X; i++) {
        long x3 = i*i*i;

        long f[20], e[20];
        long nf;

        factor(x3-1, p, np, &nf, f, e);

        long j;
        for(j = 0; j < nf; j++) {
            if(f[j] > MAX_P)
                continue;

            if(e[j] == 1 && i < f[j]) {
                printf("%ld^3 == 1 mod %ld\n", i % f[j], f[j]);
                printf("%ld^3 == 1 mod %ld\n", (i*i) % f[j], f[j]);
            }
        }
    }


    return 0;
}
