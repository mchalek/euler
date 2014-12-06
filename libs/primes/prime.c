#include <stdlib.h>
#include <stdio.h>
#include "prime.h"

bool isprime(long x, long *p, long np)
{
    if(np < 1) {
        fprintf(stderr, "ERROR: no primes!\n");
        exit(-1);
    }
    if(x > p[np-1]*p[np-1]) {
        fprintf(stderr, "ERROR: %ld is beyond the maximum testable for primes up to %ld\n", x, p[np-1]);
        exit(-1);
    }

    long i = 0;
    if(x > p[np-1]) {
        while(x) {
            // could be faster, can stop if x < p[np-1] but this requires a second check
            while(0 == (x % p[i]))
                x /= p[i];

            i++;

            if(i == np)
                break;
        }

        return x != 1;
    } else {
        // should binary search but this is the inexpensive case
        for(i = 0; i < np; i++) {
            if(p[i] == x)
                return true;
        }
    }

    return false;
}

void primes(long N, long **p, long *k)
    // simple prime sieve
{
   long i, j;
   char *iscmp = calloc(N, sizeof(char)); 
   iscmp[0] = 1;

   *p = malloc(N*sizeof(long));
   *k = 0;
   
   for(i = 2; i < N; i++) {
       if(!iscmp[i]) {
           (*p)[(*k)++] = i;
           for(j = i; j < N; j+= i) {
               iscmp[j] = 1;
           }
       }
   }

   *p = realloc(*p, (*k) * sizeof(long));
   free(iscmp);
}

long nlogi(long n, long i) {
    long ret = 0;
    if(i == 1)
        return n;

    while(!(n % i)) {
        ret++;
        n /= i;
    }

    return ret;
}

long ipow(long x, long y) {
    long i;
    if(!y)
        return 1;

    long ret = x;
    for(i = 1; i < y; i++)
        ret *= x;

    return ret;
}

void factor(
        long x,
        long primes[],
        long np,
        long *nfactors,
        long pfactors[],
        long exponents[]) {
    *nfactors = 0;

    long i, p;
    for(i = 0; i < np && x > 1; i++) {
        p = primes[i];
        if(p*p > x)
            break;

        if(!(x % p)) {
            int ind = (*nfactors)++;
            long exponent = nlogi(x, p);

            pfactors[ind] = p;
            exponents[ind] = exponent;
            x /= ipow(p, exponent);
        }
    }

    if(x > 1) { // residual must be prime
        int ind = (*nfactors)++;
        pfactors[ind] = x;
        exponents[ind] = 1;
    }
}

long num_proper_divisors(long nf, long exponents[])
{
    long ret = 1l;
    long i;

    for(i = 0; i < nf; i++)
        ret *= (exponents[i]+1);

    return ret;
}

static void accum_divisors(long total, long nf, long factors[], long exponents[], long *nout, long *out) {
    if(nf <= 0) {
        out[*nout] = total;
        (*nout)++;

        return;
    }

    long i;
    for(i = 0; i <= exponents[nf-1]; i++) {
        accum_divisors(total, nf-1, factors, exponents, nout, out);

        total *= factors[nf-1];
    }
}

void divisors(long nf, long factors[], long exponents[], long *nd_out, long **divisors_out) {
    long npd = num_proper_divisors(nf, exponents);
    long *divisors = malloc(npd*sizeof(long));
    long zero = 0;

    accum_divisors(1l, nf, factors, exponents, &zero, divisors);

    *nd_out = npd;
    *divisors_out = divisors;
}
