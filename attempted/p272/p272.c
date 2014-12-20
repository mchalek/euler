#include <prime.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long cube(long x, long m)
{
    long xmod = x % m;
    long x3 = xmod*xmod*xmod;

    return x3 % m;
}

#define MAX_P 1865706ul

int main()
{
    long np;
    long *p;

    primes(MAX_P, &p, &np);

    int *num_roots = calloc(MAX_P+1, sizeof(int));
    uint64_t i;

    for(i = 2; i < MAX_P; i++) {
        if(!(i % 1000))
            printf("doing i == %ld\n", i);
        uint64_t test = i*i + i + 1;
        long nf;
        long pfactors[20];
        long exponents[20];
        factor(test, p, np, &nf, pfactors, exponents);

        int j;
        for(j = 0; j < nf; j++) {
            if(pfactors[j] > (long) i && pfactors[j] <= (long) MAX_P) {
                //printf("%ld^3 == 1 mod %ld\n", i, pfactors[j]);
                num_roots[pfactors[j]]++;
            }
        }
    }

    long count = 0;
    for(i = 0; i < MAX_P; i++) {
        if(num_roots[i] == 2)
            count++;
    }

    printf("%d primes below %d have 3 cubed roots of unity\n", count, MAX_P);


    return 0;
}
