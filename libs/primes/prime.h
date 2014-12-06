#ifndef __PRIME_H
#define __PRIME_H

#include <stdbool.h>

void primes(long N, long **p, long *k);

bool isprime(long x, long *p, long np);

long nlogi(long n, long i);
long ipow(long x, long y);
void factor(long x, long primes[], long np, long *nfactors, long pfactors[], long exponents[]);

long num_proper_divisors(long nf, long exponents[]);
void divisors(long nf, long factors[], long exponents[], long *nd, long **divisors_out);

#endif
