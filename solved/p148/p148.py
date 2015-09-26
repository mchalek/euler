#!/usr/bin/python

# triangle mod 7 follows a sort-of fractal pattern, since row 7**i (0 based)
# always takes the form 1 0 0 ... 0 1,
# so that the tree from rows 0 to 7**i-1 is repeated on each end, summing the
# overlapping results such that after one addition the bottom row is 
# 1 0 0 ... 0 0 2 0 0 ... 0 01, and after 2 additions it is
# 1 0 0 ... 0 0 3 0 0 ... 0 0 3 0 0 ... 0 0 1,
# etc.

# number of non-multiples of 2 in a block of size 7**i is 28**i

# we can construct the total number by computing the base-7 encoding of N,
# and then putting in the biggest blocks possible first, followed by the appropriate numbers
# of smaller blocks

def decomp(n):
    # compute base-7 encoding as an array
    def encode(cur_n, k):
        if k < 0:
            return []

        x = 7**k
        nx = cur_n / x
        rx = cur_n % x
        return [nx] + encode(rx, k-1)

    k = 0
    while (7 ** k) <= n:
        k += 1

    return encode(n, k-1)

def compute(encoding):
    max_pow = len(encoding)-1

    powers = [28**i for i in range(1 + max_pow)]
    powers.reverse()

    # compute total number of non-multiples of 7
    # points is the number of starting points for sub-blocks of current size; 
    # the first sub-block is the biggest one, and it starts at the first row,
    # so initially there is just one point.  But later on, the number of points
    # grows geometrically; you can draw a simple diagram to show this.
    points = 1
    result = 0
    for (p, e) in zip(powers, encoding):
        blocks = e*(1+e)/2

        result += points*blocks*p

        points *= 1+e

    return result

print('N[100]: %d' % compute(decomp(100)))
print('N[1000000000]: %d' % compute(decomp(1000000000)))
