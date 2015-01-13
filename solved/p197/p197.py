def f(x):
    from math import *
    e = 30.403243784 - x*x
    k = pow(2, e)
    return floor(k) * 1e-9

even = -1

for i in range(1000):
    odd = f(even)

    print(even + odd)

    even = f(odd)
