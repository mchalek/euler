
def get_primes(N):
    composites = set()
    primes = [2,3] # ignore multiples of 2 or 3 via loop definition

    for p in range(5, N, 6):
        if p not in composites:
            primes.append(p)

            composites.update(range(p*p, N, 2*p))

        q = p + 2
        if q not in composites:
            primes.append(q)

            composites.update(range(q*q, N, 2*q))

    return primes

class Factorer:
    def __init__(self):
        self.max_prime = 10000000
        self.max_factor = self.max_prime**2
        self.primes = None

    def factor(self, n):
        if n > self.max_factor:
            raise Exception('Cannot factor %d: too big!!' % n)

        if self.primes is None:
            self.primes = get_primes(self.max_prime)

        n0 = n
        factors = {}
        if n is 0:
            return factors

        factors[1] = 1

        ip = 0
        while n > 1 and ip < len(self.primes):
            p = self.primes[ip]
    
            e = 0
            while 0 == (n % p):
                e += 1
                n /= p

            if e is not 0:
                factors[p] = e

            if (1+p)*(1+p) > n:
                break

            ip += 1

        if n > 1:
            factors[n] = 1

        return factors
