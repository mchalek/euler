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

def off_per(n):
    offset = A(n)

    k = 1
    z = 1

    while z != 0:
        k += 1
        z *= 10
        z += 1
        z %= n

    return (offset, k)

def getprimes(N):
    iscomp = [False]*N
    primes = []

    for p in range(2, N):
        if not iscomp[p]:
            primes.append(p)
            for q in range(p, N, p):
                iscomp[q] = True

    return primes


maxp = 1000000

target = 1000000000
num_primes = 40

primes = getprimes(maxp)

count = 0
csum = 0
for p in primes:
    if p == 2 or p == 5:
        continue
    (offset, per) = off_per(p)
    #print('%d => %d x %d' % (p, offset, per))

    if (target - offset) % per == 0:
        print('%d is a root of R(%d)' % (p, target))
        count += 1
        csum += p
        if count == num_primes:
            break

print('sum of primes: %d' % csum)
