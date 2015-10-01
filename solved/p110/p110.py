#!/usr/bin/python

def popcnt(x):
    result = 0
    while x is not 0:
        if (x & 1) is 1:
            result += 1
        x >>= 1
    return result

def mask_counts(mask, powers):
    result = 1

    for (i, p) in enumerate(powers):
        if 1 == (1 & (mask >> i)):
            result *= powers[i]

    return result

def compute(powers):
    pp = [2,3,5,7,11,13,17,19,23,29,31,37,43]
    nbits = len(powers)
    result = 0
    max_mask = 1 << nbits
    for i in range(max_mask):
        pci = popcnt(i)
        n_left = mask_counts(i, powers)
        for j in range(max_mask):
            if (i & j) is not 0:
                continue
                
            pcj = popcnt(j)
            if j > i:
                continue

            n_right = mask_counts(j, powers)

            #print('%x[%d]  %x[%d] => %d' % (i, pci, j, pcj, n_left*n_right))

            result += n_left*n_right

    product = 1
    for i in range(len(powers)):
        p = pp[i]
        product *= p**powers[i]

    print('%s => %d => %d solutions' % (str(powers), product, result))

    return (product, result)

# just manually played around until I found what seemed to work...
compute([3,3,2,2,1,1,1,1,1,1,1,1])
