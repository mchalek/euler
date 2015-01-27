#!/usr/bin/python
import sys

from math import *

#maxN = 50000000
maxN = 1000000

solcount = [0]*(maxN+1)

squares = [x*x for x in range((maxN+3)+1)]

for a in range(1,(maxN+3)/2+1):
    q = squares[2*a]
    minInd = 2*a
    while(q - squares[minInd] <= maxN):
        minInd -= 1
        if(minInd == 0):
            break
    if q - squares[minInd] > maxN:
        minInd += 1

    ws = range(minInd, 2*a+1)
    for w in ws:
        n = q-squares[w]

        solcount[n] += 1

        # check if second solution is valid
        if a > w and w > 0:
            solcount[n] += 1

result = 0
for n in range(maxN):
    if solcount[n] == 10:
        result += 1

print('result: %d' % result)
