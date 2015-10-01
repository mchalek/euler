#!/usr/bin/python
import sys

if len(sys.argv) < 2:
    print('SYNTAX: %s n' % sys.argv[0])
    sys.exit(0)

n = int(sys.argv[1])
w = 10**n

pmin = 1
pmax = 2*w

nsol = 0 
for p in range(pmin, 1+pmax):
    amin = 1
    amax = (w*(w+p)+p*p-1)/(p*p)

    for a in range(amin, 1+amax):
        if p*a > w and w*a % (p*a-w) == 0:
            b = w*a/(p*a-w)

            if a <= b:
                nsol += 1
                print('1/%d + 1/%d == %d / 10^%d' % (a, b, p, n))
print('%d solutions' % nsol)
