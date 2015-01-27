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


maxp = 1000000
n = 90

primes = set(getprimes(maxp))

count = 0
csum = 0
while count < 25 and n < maxp:
    n += 1

    if ((n % 2) == 0) or ((n % 5) == 0):
        continue

    a = A(n)

    if (n - 1) % a == 0 and n not in primes:
        count += 1
        csum += n
        print('n == %d: A(%d) == %d == %d * (%d - 1)' % (n, n, a, (n - 1) / a, n))

print('sum of first 25 values: %d' % csum)
