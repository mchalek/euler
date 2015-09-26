#!/usr/bin/python

import primes

# brute force method for testing
def brute_force_k(n, factors):
    k = 0
    for i in range(1, n):
        okay = True
        for f in factors:
            if i % f is 0:
                okay = False
                break

        if okay:
            k += 1

    return k

# let [p, d] be the set of all multiples of p that are <= d
# then let p_1,...,p_r be the set of prime factors of d
# the set of numerators <= d that are reducible with denominator d is:
# N_d = [p_1, d] U [p_2, d] U ... U [p_r, d].
# so we compute |N| via inclusion/exclusion principle, then resilience is equal to
# (|N_d| - 1) / (d-1)

def sum_groupings(group_size, n, items):
    def worker(cur_used, min_idx):
        if len(cur_used) == group_size:
            k = reduce(lambda x, y: x*y, cur_used)
            return n / k - 1

        remaining = group_size - len(cur_used)
        max_idx = len(items) - remaining
        result = 0
        for i in range(min_idx, 1 + max_idx):
            result += worker([items[i]] + cur_used, 1 + i)

        return result

    if group_size == 1:
        return sum([n / k - 1 for k in items])

    return worker([], 0)

def R(factors, extra_multiple=1):
    n = extra_multiple * reduce(lambda x, y: x * y, factors)
    m = 1
    result = 0
    for i in range(len(factors)):
        result += m*sum_groupings(1+i, n, factors)
        m *= -1

    k = n - 1 - result

    if n < 1000000:
        bfk = brute_force_k(n, factors)
        if k != bfk:
            raise Exception('Incorrect value %d for (%d-1)*R[%d] (should be %d)!' % (k, n, n, bfk))

    decimal = float(k) / (n-1)
    print('R[%d] == %d / %d ~ %.12f' % (n, k, n-1, decimal))

    if k * 94744 < 15499 * (n-1):
        print('SCORE')
    else:
        goal = float(15499) / 94744
        print('U LOSE (goal is %.12f, u exceed by %.12f)' % (goal, decimal-goal))
    print('==================================')

# testing
R([2,3], 2)
R([2,3,5,7],7)
R([2,3,5,7,11,13],4)

# more distinct primes => lower resilience
# manually play around with the number of primes until you get close to a hit;
# we are clearly looking for something that uses all primes up to and including 23;
# product of primes gets us close but we must play around with multiples of the
# smaller primes to reduce the resilience below the target threshold
# (resilience decreases asymptotically as you increase the exponent of each prime factor)
max_prime = 24
pp = primes.primes(max_prime)
R(pp, 4)
