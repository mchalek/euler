def factorial(n):
    if n == 0:
        return 1

    return n * factorial(n-1)

def ncr(n, r):
    return factorial(n) / (factorial(r) * factorial(n-r))

res = 0

for len_z in xrange(1, 9):
    for len_y in xrange(1, 10-len_z):
        len_x = 10 - len_z - len_y
        if len_x < 1:
            continue

        res += ncr(10, len_x)*factorial(len_x)*ncr(10-len_x, len_y)*factorial(len_y)*factorial(len_z)

print res / 2
