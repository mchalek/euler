#!/usr/bin/python
def get_primes(N):                                                              
    composites = set([])                                                        
    primes = [2]                                                                
                                                                                
    p = 1                                                                       
    while p < N:                                                                
        p += 2                                                                  
        if p in composites:                                                     
            continue                                                            
                                                                                
        primes.append(p)                                                        
                                                                                
        q = 2*p                                                                 
        while q < N:                                                            
            composites.add(q)                                                   
            q += p                                                              
                                                                                
    return primes                                                               

class Factorer:                                                                 
    def __init__(self):                                                         
        self.max_prime = 1000000
        self.max_factor = self.max_prime**2                                     
        self.primes = get_primes(self.max_prime)                                
                                                                                
    def factor(self, n):                                                        
        if n > self.max_factor:                                                 
            raise Exception('Cannot factor %d: too big!!' % n)                  
                                                                                
        n0 = n                                                                  
        factors = {}                                                            

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
                                                                                
factorer = Factorer()                                                           



def count(n):
    min_den = 1 + n

    max_den = n*(n+1)

    pairs = set([])
    for x in range(min_den, 1 + max_den):
        if (n*x) % (x-n) == 0:
            y = n*x / (x-n)

            if x < y:
                pair = (y, x)
            else:
                pair = (x, y)

            pairs.add(pair)

    return len(pairs)

def popcnt(x):
    result = 0
    while x is not 0:
        if (x & 1) is 1:
            result += 1
        x >>= 1
    return result

def mask_counts(mask, powers):
    result = 1

    for (i, p) in enumerate(powers):
        if 1 == (1 & (mask >> i)):
            result *= powers[i]

    return result

def compute(powers):
    pp = [2,3,5,7,11,13,17,19]
    nbits = len(powers)
    result = 0
    max_mask = 1 << nbits
    for i in range(max_mask):
        pci = popcnt(i)
        n_left = mask_counts(i, powers)
        for j in range(max_mask):
            if (i & j) is not 0:
                continue
                
            pcj = popcnt(j)
            if j > i:
                continue

            n_right = mask_counts(j, powers)

            #print('%x[%d]  %x[%d] => %d' % (i, pci, j, pcj, n_left*n_right))

            result += n_left*n_right

    product = 1
    for i in range(len(powers)):
        p = pp[i]
        product *= p**powers[i]

    #print('%s => %d => %d solutions' % (str(powers), product, result))

    return (product, result)

n = 2
num_sol = 1
done_already = set([])
max_printed = 1
while num_sol < 1000:
    n += 1
    powers = factorer.factor(n).values()
    tp = tuple(sorted(powers))
    if tp in done_already:
        continue

    done_already.add(tp)
    (pp, num_sol) = compute(powers)

    if num_sol > max_printed:
        print('%d solutions for n == %d (powers %s)' % (num_sol, pp, str(powers)))
        max_printed = num_sol

