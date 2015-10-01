#!/usr/bin/python

# very similar analysis to p110/p108
# we are looking for
#   1     1       p
#  --- + --- == -----
#   a     b      10^n
#
# or:
#
#  10^n (a + b) 
# -------------- == 1
#     p a b
#
# if we let z = gcd(x, y), and a / z == x, b / z == y, then we have:
#
#  10^n (x + y) 
# -------------- == 1
#    p z (x y)
# 
# But x + y has no factors in common with x y, so we must have:
#    10^n == x y k, for x and y coprime.  And then we must also have
#     p z == (x + y) k.
#
# We can construct the solution by first generating all coprime pairs (x, y)
# such that x y == 10^n k for some k.
# Then we know that p z == (x + y) k, such that every distinct divisor d of
# (x + y) k corresponds to a single solution, with p == d

def doit(n):
    def count_factors(pz):
        # count the divisors of the product pz == (x + y) k
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

        # compute exponents of 2 and 5 in xy == 10^n / k
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

            nf = count_factors(pz)
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
