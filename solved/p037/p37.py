#!/usr/bin/python
N = 1000000
isprime = [0] * N
composite = [0] * N

primes = []

for i in range(2,N):
    if composite[i] == 0:
        isprime[i] = 1
        primes.append(i)
        for j in range(i,N,i):
            composite[j] = 1

sum = 0
for i in primes:
    if i < 10:
        continue

    rtrunc = True
    ltrunc = True

    j = i / 10
    while j > 0:
        if isprime[j] != 1:
            rtrunc = False
            break
        j /= 10
    if not rtrunc:
        continue

    k = 10
    while k < i:
        k *= 10
    k /= 10
    while k > 1:
        j = i % k
        if isprime[j] != 1:
            ltrunc = False
            break
        k /= 10
    
    if not ltrunc:
        continue

    print('%d is right- and left- truncatable.' % i)
    sum += i

print('sum of rl-truncatable primes: %d' % sum)

