import math

def to_arr(n):
    ret = []
    while n > 0:
        ret.append(n % 10)
        n /= 10
    ret.reverse()
    return ret

def sdig(n):
    x = int(math.sqrt(n))
    r = n - x**2

    digits = to_arr(x)
    while len(digits) < 100:
        r *= 100
        x *= 10

        remainders = [r-2*x*a-a**2 for a in range(0,10)]
        r = min(filter(lambda x: x > 0, remainders))
        a = remainders.index(r)

        x += a
        digits.append(a)

    return digits

max_n = 1000

squares = set([n*n for n in range(2, 1+max_n)])
sums = [(n, sum(sdig(n))) for n in range(2, 1+max_n) if n not in squares]

for (n, dsum) in sums:
    print('sqrt[%d] => %d' % (n, dsum))

solution = sum([x[1] for x in sums])
mean = float(solution) / len(sums)
stddev = math.sqrt(sum([x[1]**2 - mean**2 for x in sums])/(len(sums)-1))

print('sum: %d' % solution)
print('average: %g +/- %g' % (mean, 2*stddev))
