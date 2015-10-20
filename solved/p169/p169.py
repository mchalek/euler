#!/usr/bin/python
from sys import argv,exit
import subprocess

def base2(n):
    if n == 0:
        return []
    z = 1l
    p = 0
    while z <= n:
        z <<= 1
        p += 1
    z >>= 1
    p -= 1
    return [p] + base2(n - z)

def count(n):
    powers = base2(n)
    num_powers = len(powers)
    intermediates = [0]*len(powers)

    intermediates[num_powers-1] = powers[num_powers-1] + 1
    for i in range(num_powers - 2, -1, -1):
        intermediates[i] += intermediates[i+1]*(powers[i]-powers[i+1])
        for j in range(i+1, num_powers-1):
            intermediates[i] += intermediates[j+1]*(powers[j]-powers[j+1]-1)
        intermediates[i] += powers[num_powers-1]

    return intermediates[0]


if len(argv) < 2:
    print('No N provided; assuming default value of 10^25')
    N = 10**25
else:
    N = int(argv[1])

print('result: %d' % count(N))

