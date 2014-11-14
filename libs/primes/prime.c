#include <stdlib.h>
#include "prime.h"

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

