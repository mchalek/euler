import sys, cftools

max_N = 10000
num_odd = 0
for N in range(2,max_N+1):
    (coeffs, period) = cftools.compute_coeffs(N)
    print('sqrt(%d) == %s (period %d)' % (N, cftools.to_string(coeffs, period), period))

    if (period % 2) != 0:
        num_odd += 1

print('%d odd periods for N <= %d' % (num_odd, max_N))
