#!/usr/bin/python

primes = set([2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97])
def check(N):
    import itertools

    perms = itertools.permutations(range(1, 1+N))

    counts = [0]*26
    for p in perms:
        n_nat = 0
        for (idx, item) in enumerate(p):
            n = idx + 1
            if item == n and n in primes:
                n_nat += 1

        counts[n_nat] += 1

    return counts

def compute(N):
    if N > 100:
        raise

    # for list of [1], no primes, only one possibly arrangment
    counts = [0]*26
    counts[0] = 1

    np = 0 # keep count of number of primes in growing permutation
    for i in range(2, N+1):
        # i-1 items in already-built-and-accounted set
        # first count swaps of current entry with an earlier one.  n_nat ways to choose an earlier naturally-located
        # prime, i-1-n_nat ways to choose an earlier composite or non-naturally-located prime.
        # So n_nat ways to go from n_nat to n_nat-1, and i-1-n_nat ways to remain at n_nat
        # {123,+132,213,+231,+312,321} come from {12+, 12x, 21+, 21x, 21x, 12x}
        next_counts = [0]*26
        for (n_nat, j) in enumerate(counts):
            next_counts[n_nat] += j * (i-1-n_nat)
            if n_nat > 0:
                next_counts[n_nat-1] += j * n_nat

        if i in primes:
            # can also go from n_nat to n_nat + 1 by putting current entry in its place
            for (n_nat, j) in enumerate(counts):
                if j == 0:
                    break
                next_counts[1 + n_nat] += j

            np += 1
        else:
            # can also go from n_nat to n_nat by putting current entry in its place
            for(n_nat, j) in enumerate(counts):
                if j == 0:
                    break
                next_counts[n_nat] += j

        counts = next_counts
    return counts

#for n in range(10):
#    print(('compute(%d): ' % n) + str(compute(n)))
#    print(('check(%d): ' % n) + str(check(n)))

#counts = compute(100)
#print('compute(100): ' + str(compute(100)))
