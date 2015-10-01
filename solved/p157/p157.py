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

def doit(n):
    def count_factors(x, y, pz, k):
        if pz == 1:
            return 1

        result = 2 # automatically count (1, pz)
        i = 2

        while i*i <= pz:
            if (pz % i) == 0:
                j = pz / i

                if i != j:
                    result += 2
                else:
                    result += 1
            i += 1
        return result

    def for_k(kparm):
        (k2, k5) = kparm # parameterize k by number of 2 and 5 factors
        k = 2**k2*5**k5
        xy2 = n-k2
        xy5 = n-k5

        # up to 2 different ways to factor xy as coprime pair, given that there
        # are only 2 prime factors
        if xy2 is 0 and xy5 is 0:
            xy = [(1,1)]
        elif xy2 is 0:
            xy = [(5**xy5, 1)]
        elif xy5 is 0:
            xy = [(2**xy2, 1)]
        else:
            xy = [(2**xy2 * 5**xy5, 1), (5**xy5, 2**xy2)]

        result = 0
        for (x, y) in xy:
            pz = k*(x + y)

            nf = count_factors(x, y, pz, k)
            result += nf

        return result

    result = 0
    for k2 in range(1+n):
        for k5 in range(1+n):
            result += for_k((k2, k5))

    return result

result = 0
for n in range(1,10):
    nn = doit(n)
    result += nn

    print('number of solutions for n == %d: %d' % (n, nn))

print('total number of solutions for 1 <= n <= 9: %d' % result)
