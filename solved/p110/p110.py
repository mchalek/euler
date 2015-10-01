#!/usr/bin/python

# same as p108
# we are looking for
#   1     1      1
#  --- + --- == --- 
#   x     y      n
#
# or:
#
#  n (x + y) 
# ----------- == 1
#      x y
#
# if we let z = gcd(x, y), and x / z == a, y / z == b, then we have:
#
#  n (a + b) 
# ----------- == 1
#   z (a b)
# 
# But a + b has no factors in common with a b, so we must have:
#    n == a b k, for a and b coprime.  And then we must also have
#    z == (a + b) k.
#
# Then the number of distinct solutions is equal to the number of distinct
# ways to draw a pair of coprime values, a and b, such that a*b is a divisor
# of n.  We can compute this with a straightforward exhaust.
#
# Note that we can recover x and y for a given choice of a, b and k via:
#  x = (a + b) k a
#  y = (a + b) k b,
# but it is unnecessary for this problem.

def mask_counts(mask, powers):
    result = 1

    for (i, p) in enumerate(powers):
        if 1 == (1 & (mask >> i)):
            result *= powers[i]

    return result

def compute(powers):
    pp = [2,3,5,7,11,13,17,19,23,29,31,37,43]
    nbits = len(powers)
    result = 0
    max_mask = 1 << nbits
    for i in range(max_mask):
        n_left = mask_counts(i, powers)
        for j in range(1 + i):
            if (i & j) is not 0:
                continue
                
            n_right = mask_counts(j, powers)

            result += n_left*n_right

    product = reduce(lambda x, y: x*y, [pp[i]**e for (i, e) in enumerate(powers)])

    print('%s => %d => %d solutions' % (str(powers), product, result))

    return (product, result)

# just manually played around until I found what seemed to work...
compute([3,3,2,2,1,1,1,1,1,1,1,1])
