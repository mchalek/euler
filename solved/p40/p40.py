#!/usr/bin/python
def digits(a):
    ret = []
    while a != 0:
        ret.append(a % 10)
        a /= 10

    ret.reverse()
    return ret

l = []
k = 1
while len(l) < 1000000:
    l += digits(k)
    k += 1

for n in range(20):
	print('d(%d): %d' % (n,l[n]))

p = 1
for n in range(7):
    print('d_%d: %d' % (10**n, l[10**n-1]))
    p *= l[10**n-1]

print('product: %d' % p)
