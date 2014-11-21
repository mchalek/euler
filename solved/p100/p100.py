from cftools import *

a = 0

while True:
    a += 1
    coeffs = [1] + [2]*a
    (x,y) = get_term(coeffs)

    #print('%d / %d' % (x, y))
    if (x % 2) == 1 and (y % 2) == 1:
        N = x / 2 + 1
        k = y / 2 + 1
        print('solution: %d / %d' % (k, N))

        if N >= 1e12:
            break
    
