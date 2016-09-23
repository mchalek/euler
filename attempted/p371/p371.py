#!/usr/bin/python

# must track the number of all-zero plates drawn

N = 500

result = 0.0
pn = [999.0 / 1000, 1.0 / 1000] # coincides with n=1 case
for n in range(2, N):
    ptmp = [0.0]*(n+1)
    for j in range(n):
        nnz = n - 1 - j

        p_all_zero = 1.0 / 1000
        p_hit = (1.0 - (998.0/999)**nnz)
        ptmp[j] += (1.0-p_hit)*pn[j]

        ptmp[j+1] += p_all_zero*pn[j]

    p_delta = sum(pn)-sum(ptmp)
    result += p_delta*n
    print('at n == %d, p_delta == %f, result == %f' % (n, p_delta, result))
    pn = ptmp

print('result: %f' % result)
