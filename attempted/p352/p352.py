#!/usr/bin/python

import math

def Z(j, p):
    return (j-1)*(1-p)**(j-1) + j*(1-(1-p)**(j-1))

N = 25

p = 0.02

nunk = [0 for i in range(N+1)] # tests if not known contaminated
nk = [0 for i in range(N+1)] # tests if known contaminated

nunk[1] = 1

nk[1] = 0
nk[2] = 1*(1-p) + 2*p

for i in range(2,N+1):
# first handle case where we know it's contaminated
#worst case is we test first n-1 and then decide whether to do last one
    nmin = (i-1)*(1-p)**(i-1) + i*(1-(1-p)**(i-1))

    for j in range(1, i+1):
        # try dividing in two, one of size j, one of (i-j)
        ntest = ()*(1-p)**j




    nmin = i

    for j in range(1, i+1):
        # strategy is to mix together j samples,
        # then take the optimal solution for (i-j)

        ntest = 1 + Z(j,p) * (1-(1-p)**j) + nunk[i-j]
        if ntest < nmin:
            nmin = ntest

    nunk[i] = nmin

print(nunk)

