#!/usr/bin/python

N = 15
ways = [0 for i in range(N+1)]

ways[0] = 1
ways[1] = 1

for i in range(2, N+1):
    for j in range(i/2, i):
        ways[i] += ways[j]

    print ways
