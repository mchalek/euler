import cftools 

def digsum(n):
    s = 0
    while n > 0:
        s += n % 10
        n /= 10
    return s

term_num = 100

e_coeffs = [2]
k = 1
while len(e_coeffs) < term_num:
    e_coeffs += [1, 2*k, 1]
    k += 1

e_coeffs = e_coeffs[0:term_num]
(n, d) = cftools.get_term(e_coeffs)

print('%d / %d is the %dth c-f approximation of e' % (n, d, term_num))
print('sum of digits in the numerator is: %d' % digsum(n))
