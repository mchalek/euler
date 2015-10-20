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

if len(argv) < 2:
    print('No N provided; assuming default value of 10^25')
    N = 10**25
else:
    N = int(argv[1])

powers = base2(N)

args = ['./p169'] + map(str, powers)
subprocess.call(args)

