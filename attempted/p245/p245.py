#!/usr/bin/python

import primes

# let [p, d] be the set of all multiples of p that are <= d
# then let p_1,...,p_r be the set of prime factors of d
# the set of numerators <= d that are reducible with denominator d is:
# N_d = [p_1, d] U [p_2, d] U ... U [p_r, d].
# so we compute |N| via inclusion/exclusion principle, then resilience is equal to
# (d - |N_d|) / (d-1)


# sum_groupings computes the sum of cardinalities of all intersections
# [p_a, d] & [p_b, d] & ... & [p_g, d]
# of size group_size, where items[] is the list of prime factors of d
def sum_groupings(group_size, d, items):
    def worker(cur_used, min_idx):
        if len(cur_used) == group_size:
            k = reduce(lambda x, y: x*y, cur_used)
            return d / k

        remaining = group_size - len(cur_used)
        max_idx = len(items) - remaining
        result = 0
        for i in range(min_idx, 1 + max_idx):
            result += worker([items[i]] + cur_used, 1 + i)

        return result

    if group_size == 1:
        return sum([d / k for k in items])

    return worker([], 0)

def R(factors, extra_multiple=1):
    d = extra_multiple * reduce(lambda x, y: x * y, factors)
    m = 1
    result = 0
    for i in range(len(factors)):
        result += m*sum_groupings(1+i, d, factors)
        m *= -1

    k = d - result

    decimal = float(k) / (d-1)
    print('R[%d] == %d / %d ~ %.12f' % (d, k, d-1, decimal))

    if k * 94744 < 15499 * (d-1):
        print('SCORE')
    else:
        goal = float(15499) / 94744
        print('U LOSE (goal is %.12f, u exceed by %.12f)' % (goal, decimal-goal))
    print('==================================')

    return (k, d-1)

pp = primes.primes(100)
r = 1
k = 0
pz = []
while r < 200000000000:
   r *= pp[k]
   pz.append(pp[k])
   k += 1
(num, den) = R(pz, 1)

print('max denominator for coresilience problem 245 is %d' % (den / num))

