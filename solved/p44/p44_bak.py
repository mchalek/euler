#!/usr/bin/python

import math

known_mindist = 5482660  # empirical 

Npen = 40000

P = []

for i in range(1, Npen+1):
    val = i*(3*i-1)/2
    P.append(val)

print P[0:100]
    
nhit = 0
mindist = None
for i in range(Npen):
    p = P[i]
    
    for j in range(i-1):
        q = P[j]
        s = p+q
        stest = (1. + math.sqrt(1+24*s)) / 6.
        if stest != math.floor(stest):
            continue

        d = abs(p-q)
        dtest = (1. + math.sqrt(1+24*d)) / 6.
        if dtest != math.floor(dtest):
            continue

        print("%d/%d %d + %d == %d   |%d-%d| == %d" % (p, q, p, q, p+q, p, q, d))
        if mindist == None:
            mindist = d
        elif mindist > d:
            mindist = d
        nhit += 1

print('%d satisfactory pairs' % nhit)
print('terminal distance: %d' % (P[-1]-P[-2]))
print('mindist: %d' % mindist)
if mindist <= (P[-1]-P[-2]):
    print 'answer is guaranteed'
else:
    print 'answer not guaranteed.  Try bigger N'
