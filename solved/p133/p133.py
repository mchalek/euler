def A(n):
    k = 1
    r = 1
    while r < n:
        r *= 10
        r += 1
        k += 1

    z = r % n

    while z != 0:
        k += 1
        z *= 10
        z += 1
        z %= n

    return k

def getprimes(N):
    iscomp = [False]*N
    primes = []

    for p in range(2, N):
        if not iscomp[p]:
            primes.append(p)
            for q in range(p, N, p):
                iscomp[q] = True

    return primes

def reduceby(x, n):
    while 0 == x % n:
        x /= n

    return x

maxp = 100000

target = 1000000000
num_primes = 40

primes = getprimes(maxp)

csum = 2 + 5 # we know these won't
for p in primes:
    if p == 2 or p == 5:
        continue
    a = A(p)

    b = reduceby(a, 2)

    c = reduceby(b, 5)

    if c != 1:
        #print('%d can never be a factor of R(10^n)' % p)
        csum += p
    #else:
        #print('%d CAN be a factor of R(10^n)' % p)

print('sum of primes: %d' % csum)
