def dsum(x):
    ret = 0
    while x > 0:
        ret += x % 10
        x /= 10

    return ret

hits = set()

MAX = 10**16

for i in range(2, 100):
    x = i
    while x < MAX:
        if dsum(x) == i and x > 9:
            hits.add(x)
        x *= i

items = sorted(list(hits))
print('found %d hits' % len(items))
print('set contents: ' + (','.join([str(x) for x in items])))

if len(items) > 29:
    print('solution: %d' % items[29])


