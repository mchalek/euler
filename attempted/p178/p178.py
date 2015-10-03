#!/usr/bin/python
import sys

def ispan(digits):
    return len(set(digits)) == 10

def compute(digits, ndig):
    if len(digits) > ndig:
        return 0

    count = 0
    if ispan(digits):
        print(''.join(map(str, digits)))
        count = 1

    last_dig = digits[-1]
    if last_dig == 0:
        return count + compute(digits + [1], ndig)
    elif last_dig == 9:
        return count + compute(digits + [8], ndig)
    else:
        return count + compute(digits + [last_dig-1], ndig) + compute(digits + [last_dig+1], ndig)

if len(sys.argv) < 2:
    print('SYNTAX: %s ndig' % sys.argv[0])
    sys.exit(0)

ndig = int(sys.argv[1])

hits = 0
for i in range(1, 10):
    hits += compute([i], ndig)

print('%d hits for length %d' % (hits, ndig))
        
