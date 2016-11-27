from __future__ import print_function

# pretty dumb approach:
# a^2 == x + y
# b^2 == x - y
# c^2 == y + z
# d^2 == y - z
# e^2 == x + z
# f^2 == x - z
# 
# or, equivalently:
# x = (a^2 + b^2) / 2 == (c^2 + d^2) / 2
# y = (a^2 - b^2) / 2 == (e^2 + f^2) / 2
# z = (c^2 - d^2) / 2 == (e^2 - f^2) / 2
# 
# where each of a, ..., f is unique
# 
# We first pre-generate lists of all even sums- and differences-of-squares.
# The intersection of these lists forms the candidate for values of y.  Now we
# just brute-force search over these in order to find values of y that are
# generated from an (a/b/c/d) that also generate an x/z pair that satisfies the
# requirements.

def test_hit(sum_pair, diff_pair, squares):
    hits = []
    for (a, b) in sum_pair:
        y = (a**2 + b**2) / 2
        z = (a**2 - b**2) / 2
        for (c, d) in diff_pair:
            x = (c**2 + d**2) / 2

            print('y == %d; z == %d; x == %d' % (x, y, z), end='')

            if x + z not in squares:
                print(' => FAIL')
                continue

            if x - z not in squares:
                print(' => FAIL')
                continue

            print(' => PASS')
            print('(generator: (%d, %d), (%d, %d)' % (a, b, c, d))

            hits.append([x, y, z])

    return hits

N = 1000 # 1000 is enough to find the solution

sums = {}
diffs = {}

for a in xrange(1, N):
    for b in xrange(1+a, N):
        s = b**2 + a**2
        if s % 2:
            continue
        s /= 2
        sums.setdefault(s, [])
        sums[s].append((b, a))

for a in xrange(1, N):
    for b in xrange(1+a, N):
        d = b**2 - a**2
        if d % 2:
            continue
        d /= 2
        diffs.setdefault(d, [])
        diffs[d].append((b, a))

squares = set([x*x for x in xrange(2*N)])

possible_y = set(sums.keys()) & set(diffs.keys())

all_hits = []

for y in possible_y:
    hits = test_hit(sums[y], diffs[y], squares)

    if len(hits) == 0:
        continue

    print('hits found: %s' % str(hits))
    all_hits += hits

for hits in all_hits:
    print('solution: %s => %d' % (str(hits), sum(hits)))
