#!/usr/bin/python

import math

mindist = 5482660  # empirical from search of all possibilities

P = [1,5]

i = 2
jmin = 0
stopcond = False

while not stopcond:
    i += 1
    p = i*(3*i-1)/2

    P.append(p)

    while P[jmin] + mindist < p:
        jmin += 1

    for j in range(jmin, i):
        q = P[j]
        s = p+q
        stest = (1. + math.sqrt(1+24*s)) / 6.
        if stest != math.floor(stest):
            continue

        d = p-q
        dtest = (1. + math.sqrt(1+24*d)) / 6.
        if dtest != math.floor(dtest):
            continue

        print("%d/%d %d + %d == %d   |%d-%d| == %d" % (p, q, p, q, p+q, p, q, d))
        if d < mindist:
            mindist = d

    if mindist < (P[-1]-P[-2]):
        stopcond = True

print('mindist: %d' % mindist)
print('had to test up to i == %d' % i)
