#!/usr/bin/python

valid_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
max_powers =   [6, 4, 2, 2,  1,  1,  1,  1,  1,  1,  1,  1]

def build(max_exponents):
    results = []
    def build(ex):
        if len(ex) == len(valid_primes):
            results.append(ex)
            return

        ind = len(ex)
        for e in range(1 + max_exponents[ind]):
            build(ex + [e])
        
    build([])

    return results

def generate_gcd():
    return build(max_powers)

def count_coprime(gcd):
    from Queue import Queue

    def build_residuals(primes_used):
        max_powers_lcl = [0 if used else e for (e, used) in zip(max_powers, primes_used)]

        def merge_used(ex):
            return [(ex[i] | primes_used[i]) for i in range(len(ex))]

        residuals_factored = build(max_powers_lcl)

        return [(merge_used(ex), None) for ex in residuals_factored]

    primes_used_by_gcd = [e > 0 for e in gcd]
    q = []
    q.append((primes_used_by_gcd, set())) # store used_primes bitfield and list of residuals

    print('primes used by gcd: %s' % str(primes_used_by_gcd))

    print('num residuals: %d' % len(build_residuals(primes_used_by_gcd)))

    count = 0
    while len(q) > 0:
        (primes_used, current_residuals) = q[0]
        q = q[1:]


        next_residuals = build_residuals(primes_used)
        print('got: %s, begets %d new ones' % (','.join(map(str, current_residuals)), len(next_residuals)))
        for (new_primes_used, next_residual) in next_residuals:
            done = all(new_primes_used)

            if done:
                continue

            if next_residual in current_residuals:
                # should only happen for 1
                continue

            new_residuals = current_residuals | set([next_residual])
            q.append((new_primes_used, new_residuals))
            count += 1

    return count

gcds = generate_gcd()

print len(gcds)

print('gcds[20000]: %s' % str(gcds[20000]))

print count_coprime(gcds[20000])
