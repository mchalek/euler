#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define N 64000000

// This one is pretty straightforward; generate the full table of sigma(n)
// via a sieve, and then go through and look for perfect squares.  There may
// be smarter ways, but this one runs in under a minute so I'm fine with it.

int cmp(const void *va, const void *vb)
{
    long a = *((long *) va);
    long b = *((long *) vb);

    return (a > b) ? 1 : ((a == b) - 1);
}

int main(void)
{
    long *sigma = calloc(N, sizeof(long));
    long i;

    for(i = 1; i < N; i++) {
        long i2 = i*i;
        long j;
        for(j = i; j < N; j += i) {
            sigma[j] += i2;
        }
    }

    fprintf(stderr, "generated sigma(n)\n");
    fprintf(stderr, "sigma(10) == %ld\n", sigma[10]);

    long max_sigma = 0;
    for(i = 1; i < N; i++) {
        max_sigma = (max_sigma < sigma[i]) ? sigma[i] : max_sigma;
    }

    fprintf(stderr, "max_sigma: %ld\n", max_sigma);
    long max_sqrt = (long) ceil(sqrt(max_sigma));
    long *squares = malloc((1+max_sqrt)*sizeof(long));
    for(i = 0; i <= max_sqrt; i++) {
        squares[i] = i*i;
    }
    fprintf(stderr, "generated squares up to %ld^2\n", max_sqrt);

    long sum = 0l;
    for(i = 1; i < N; i++) {
        long target = sigma[i];
        bool hit = bsearch(&target, squares, 1+max_sqrt, sizeof(long), cmp) ? i : 0;

        sum += hit ? i : 0;
        if(hit)
            fprintf(stderr, "hit on sigma(%ld) == %ld\n", i, sigma[i]);
    }
    fprintf(stderr, "result: %ld\n", sum);

    return 0;
}
