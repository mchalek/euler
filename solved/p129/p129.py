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

n = 1000000
mxa = 0
mxn = 0
stop = False
while not stop:
    n += 1
    if 0 == (n % 10000):
        print('tested n == %d, max A is %d == A(%d)' % (n, mxa, mxn))

    if ((n % 2) == 0) or ((n % 5) == 0):
        continue

    a = A(n)
    if a > mxa:
        mxa = a
        mxn = n

    #print('A(%d) == %d' % (n, a))
    if a > 1000000:
        print('A(%d) == %d' % (n, a))
        stop = True
