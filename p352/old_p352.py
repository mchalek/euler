#!/usr/bin/python

import math

def p_setj_clear(p, N, j):
    ret = 0
    for n in range(1,N+1):
        if N-j < n:
            continue
        ret += p**n * (1-p)**(N-n) / (1-(1-p)**N) * math.factorial(N-j) / math.factorial(n) / math.factorial(N-j-n)

    return ret

p = 0.02
ntests = [0,1] # number of tests needed if nothing known
ntests_known = [0,1] # number of tests needed if population is known contaminated

for i in range(2,26):
    # first find the number of tests needed if current group is
    # known to be contaminated
    nt_min = i # worst case is to check every sheep

    # can also partition into independent groups and treat each
    # as contaminated
    for j in range(1,i):
        nt_try = ntests_known[j] + ntests_known[i-j]
        if nt_min > nt_try:
            nt_min = nt_try;

    # can also partition and mix each partition, here probability of 
    # a group being contaminated must be computed
    for j in range(1,i):
        pworked_j = p_setj_clear(p, i, j)
        pworked_imj = p_setj_clear(p, i, i-j)
        nt_try = 1 + pworked_j*ntests_known[i-j] + (1-pworked_j)*(ntests_known[j] + 1 + (1-pworked_imj)*ntests_known[i-j])
        if nt_min > nt_try:
            nt_min = nt_try
        nt_try = 1 + pworked_j*ntests_known[i-j] + (1-pworked_j)*(ntests_known[j] + ntests_known[i-j])
        if nt_min > nt_try:
            nt_min = nt_try

    ntests_known.append(nt_min);

    opt = 0

    nt_min = ntests[1] + ntests[i-1] # one option is just to partition
    for j in range(2,i):
        nt_try = ntests[j] + ntests[i-j]
        if nt_try < nt_min:
            opt = 1
            nt_min = nt_try

    # another is to partition and mix both
    for j in range(1, i):
        nt_try = 2 + (1-(1-p)**j)*ntests_known[j] + (1-(1-p)**(i-j))*ntests_known[i-j]
        if nt_try < nt_min:
	    nt_min = nt_try
            opt = 2
 
    # another is to partition and mix one
    for j in range(i):
        nt_try = 1 + (1-(1-p)**(i-j))*ntests_known[i-j] + ntests[j]
        if nt_try < nt_min:
            opt = 4
            nt_min = nt_try           

    ntests.append(nt_min)

print ntests_known
print ntests
