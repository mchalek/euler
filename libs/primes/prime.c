#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "prime.h"
#include <miller_rabin.h>

int lcmp(const void *va, const void *vb)
{
    long a = *((long *) va);
    long b = *((long *) vb);

    return (a == b) ? 0 : (2 * (a > b) - 1);
}

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

    if(x <= p[np-1])
        return NULL != bsearch(&x, p, np, sizeof(long), lcmp);

    // do miller-rabin for speedy first-pass check
    if(!mr_isprime(x))
        return false;

    // we want determinism, so if miller-rabin says it's prime, 
    // confirm via brute force
    long i = 0;
    for(i = 0; i < np; i++) {
        if(p[i]*p[i] >= x)
            break;

        if(0 == (x % p[i]))
            return false;
    }

    return true;
}

static inline void cmpidx(long x, long *idx, uint64_t *mask)
{
    *idx = x / 128;
    *mask = 1ul << ((x % 128) >> 1);
}

static inline bool iscmp(long x, uint64_t *cmp)
{
    long idx;
    uint64_t mask;
    cmpidx(x, &idx, &mask);

    return cmp[idx] & mask;
}

static inline void setcmp(long x, uint64_t *cmp)
{
    long idx;
    uint64_t mask;
    cmpidx(x, &idx, &mask);

    cmp[idx] |= mask;
}

void primes(long N, long **p, long *k_out)
    // simple prime sieve
{
   if(N < 2) {
       fprintf(stderr, "ERROR: no primes < 2!!\n");
       exit(-1);
   }

   uint64_t i, j;
   uint64_t uiN = (uint64_t) N; // we know conversion is okay because N >= 2
   uint64_t nword = (uiN + 127) / 128;
   uint64_t *cmp = aligned_alloc(16, nword * sizeof(uint64_t));
   memset(cmp, 0, nword * sizeof(uint64_t));

   long nalloc = 1024;
   *p = malloc(nalloc*sizeof(long));
   long k = 0;

   (*p)[k++] = 2;

   for(i = 3; i < uiN; i += 2) {
       if(!iscmp(i, cmp)) {
           if(k == nalloc) {
               nalloc <<= 1;
               *p = realloc(*p, nalloc*sizeof(long));
           }
           (*p)[k++] = (long) i;
           
           // check for i^2 overflow
           // not a problem because we're assured N fits in 64 bits
           if(i > ((1ul << 32) - 1))
               continue;

           for(j = i*i; j < uiN; j += 2*i) {
               setcmp(j, cmp);
           }
       }
   }

   free(cmp);
   *p = realloc(*p, k * sizeof(long));
   *k_out = k;
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
            pfactors[ind] = p;
            exponents[ind] = 1;
            x /= p;
            while(!(x % p)) {
                exponents[ind]++;
                x /= p;
            }
        }
    }

    if(x > 1) { // residual must be prime
        int ind = (*nfactors)++;
        pfactors[ind] = x;
        exponents[ind] = 1;
    }
}

void merge_factors(long nf0, long factors0[], long exponents0[],
        long nf1, long factors1[], long exponents1[],
        long *nf2_out, long factors2[], long exponents2[])
{
    // this is a wasteful algorithm but it may not matter
    *nf2_out = nf0;

    memcpy(factors2, factors0, nf0*sizeof(long));
    memcpy(exponents2, exponents0, nf0*sizeof(long));

    long i, j;
    for(i = 0; i < nf1; i++) {
        for(j = 0; j < nf0; j++) {
            if(factors0[j] == factors1[i]) {
                exponents2[j] += exponents1[i];
                break;
            }
        }

        if(j == nf0) {
            exponents2[*nf2_out] = exponents1[i];
            factors2[(*nf2_out)++] = factors1[i];
        }
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

static void accum_divisors(long min, long max, long total, long nf, long factors[], long exponents[], long *nout, long *out) {
    if(max >= 0 && total > max)
        return;

    if(nf <= 0) {
        if(min >= 0 && total < min) {
            return;
        }

        out[*nout] = total;
        (*nout)++;

        return;
    }

    long i;
    for(i = 0; i <= exponents[nf-1]; i++) {
        accum_divisors(min, max, total, nf-1, factors, exponents, nout, out);

        total *= factors[nf-1];
    }
}

void divisors(long nf, long factors[], long exponents[], long *nd_out, long **divisors_out) {
    long npd = num_proper_divisors(nf, exponents);
    long *divisors = malloc(npd*sizeof(long));
    long zero = 0;

    accum_divisors(-1, -1, 1l, nf, factors, exponents, &zero, divisors);

    *nd_out = npd;
    *divisors_out = divisors;
}

void bounded_divisors(long min, long max, long nf, long factors[], long exponents[], long *nd_out, long **divisors_out) {
    long npd = num_proper_divisors(nf, exponents);
    long *divisors = malloc(npd*sizeof(long));

    npd = 0;

    accum_divisors(min, max, 1l, nf, factors, exponents, &npd, divisors);

    *nd_out = npd;
    *divisors_out = divisors;
}

void reduce(long n, long d, long np, long p[], long *n_red, long *d_red) {
    long i;
    long mx = (n < d) ? n : d;

    // do a prime factorization of smaller of n and d, and then reduce
    // the pair together as is possible
    long nf; // num factors
    long factors[32];
    long exponents[32];
    factor(mx, p, np, &nf, factors, exponents);

    for(i = 0; i < nf; i++) {
        while(!(n % factors[i]) && !(d % factors[i])) {
            n /= factors[i];
            d /= factors[i];
        }
    }

    *n_red = n;
    *d_red = d;
}

