import cftools
import sys

max_x = 0
maxx_D = 0

for D in range(2,1001):
    (coeffs, period) = cftools.compute_coeffs(D)

    if period == 0: # perfect square
        continue

    if period != len(coeffs) - 1:
        print("can't handle the c-f rep for sqrt(%d): %s" % (D, to_string(coeffs, period)))
        sys.exit(0)

    my_coeffs = [coeffs[0]]
    rep = coeffs[1:]
    k = 0

    while True:
        (x, y) = cftools.get_term(my_coeffs)

        num = (x+1)*(x-1)
        den = y**2

        if num - D*den == 0:
            break

        my_coeffs.append(rep[k])
        k += 1
        k %= len(rep)

    if x > max_x:
        maxx_D = D
        max_x = x
    print('solution found for D == %d: (%d, %d)' % (D, x, y))

print('D == %d yields the largest value for x (== %d)' % (maxx_D, max_x))
