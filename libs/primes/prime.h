#ifndef __PRIME_H
#define __PRIME_H

#include <stdbool.h>

void primes(long N, long **p, long *k);

bool isprime(long x, long *p, long np);

long nlogi(long n, long i);
long ipow(long x, long y);
void factor(long x, long primes[], long np, long *nfactors, long pfactors[], long exponents[]);

void reduce(long n, long d, long np, long p[], long *n_red, long *d_red);

long num_proper_divisors(long nf, long exponents[]);
void divisors(long nf, long factors[], long exponents[], long *nd, long **divisors_out);
void bounded_divisors(long min, long max, long nf, long factors[], long exponents[], long *nd_out, long **divisors_out);

void merge_factors(long nf0, long factors0[], long exponents0[],
        long nf1, long factors1[], long exponents1[],
        long *nf2_out, long factors2[], long exponents2[]);

#endif
