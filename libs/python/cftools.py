import sys

# construct integer square roots
k = 1
isqrts = [0]
while len(isqrts) <= 10000:
    count = 2*k + 1
    isqrts += [k]*count
    k += 1

def compute_coeffs(N):
    root = isqrts[N]
    coeffs = [root]
    if root**2 == N:
        return [coeffs, 0]
    carry_num = 1
    carry_den = -root
    iteration = 0

    used = {carry_num: [(carry_den, iteration)]}

    period = None
    while period == None:
       iteration += 1

       divisor = N - carry_den**2
       if divisor % carry_num != 0:
           # this seems impossible but i haven't proven it
           print('N == %d: FUCK!' % N)
           sys.exit(0)

       divisor /= carry_num
       numerator = root - carry_den
       coeffs.append(numerator / divisor)
       rem = numerator % divisor

       carry_den = rem - root
       carry_num = divisor

       previous = used.setdefault(carry_num, [])
       for (p,q) in previous:
           if p == carry_den:
               period = iteration - q

       previous.append((carry_den, iteration))

       used[carry_num] = previous

    return (coeffs, period)

def to_string(coeffs, period):
    if period == 0:
        return '%d' % coeffs[0]

    rep_ix = len(coeffs)-period

    singles = coeffs[1:rep_ix]
    single_str = ','.join([str(i) for i in singles])
    reps = coeffs[rep_ix:]
    rep_str = '(%s)' % ','.join([str(i) for i in reps])

    if len(single_str) > 0:
        # seems like this might never happen?
        tail = '%s, %s' % (single_str, rep_str)
    else:
        tail = rep_str

    return '[%d; %s]' % (coeffs[0], tail)
def update(a, num, den):
    new_den = a*den + num
    new_num = den

    return (new_num, new_den)

def get_term(coeffs):
    num = 1
    den = coeffs[-1]
    for a in reversed(coeffs[0:-1]):
        (new_num, new_den) = update(a, num, den)

        num = new_num
        den = new_den

    return (den, num) # reverse order
