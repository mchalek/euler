#include <prime.h>
#include <stdlib.h>
#include <stdio.h>

#define ELEMENT_INDEX 10000
#define N 100000

typedef struct _nr {
    long n;
    long rad;
} nr_t;

int cmp_rad(const void *va, const void *vb)
{
    const nr_t *a = va;
    const nr_t *b = vb;

    if(a->rad == b->rad) {
        if(a->n == b->n)
            return 0;
        else return (a->n < b->n) ? -1 : 1;
    } else {
        return (a->rad < b->rad) ? -1 : 1;
    }
}

int main()
{
    long *p, np;
    primes(N, &p, &np);

    nr_t *rad = malloc((N+1)*sizeof(nr_t));
    rad[0].n = 0;
    rad[0].rad = 0;
    rad[1].n = 1;
    rad[1].rad = 1;

    long n;
    for(n = 2; n <= N; n++) {
        long nfactors;
        long factors[20];
        long exponents[20];

        factor(n, p, np, &nfactors, factors, exponents);

        int i;
        rad[n].n = n;
        rad[n].rad = 1l;
        for(i = 0; i < nfactors; i++) {
            rad[n].rad *= factors[i];
        }
    } 

    qsort(rad, 1+N, sizeof(nr_t), cmp_rad);

    printf("element %d == (%ld, %ld)\n",
            ELEMENT_INDEX, rad[ELEMENT_INDEX].n, rad[ELEMENT_INDEX].rad);

    return 0;
}
