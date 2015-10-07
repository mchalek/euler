#!/usr/bin/python

from primes import get_primes

# pretty simple, just determine for each prime, p, the set of primes
# {q: q >= p && p*q < Nmax}.  Each of these items contributes a single
# count to the result.

NMAX = 100000000

primes = get_primes(NMAX)

result = 0
lastptr = -1
for (ip, p) in enumerate(primes):
    q = primes[lastptr]
    while p*q >= NMAX:
        lastptr -= 1
        q = primes[lastptr]

    if q < p:
        break

    num_items = len(primes) + 1 + lastptr - ip
    result += num_items

print(result)


