
def get_primes(N):
    is_comp = [False for x in range((N+1)/2)]
    primes = [2,3] # ignore multiples of 2 or 3 via loop definition

    for p in range(5, N, 6):
        if not is_comp[(p-1)/2]:
            primes.append(p)

            for r in range(p*p, N, 2*p):
                is_comp[(r-1)/2] = True 

        q = p + 2
        if not is_comp[(q-1)/2]:
            primes.append(q)

            for r in range(q*q, N, 2*q):
                is_comp[(r-1)/2] = True

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
