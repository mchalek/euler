#include<prime.h>
#include<stdio.h>

// the code here is working but it's too brute-force to get to the target solution
// in a reasonable amount of time.
//
// ** UPDATE **: actually it only took a few mins.  But still the approach below
// would be much better.
//
// for the target reflection count, the "depth" in the virtual reflection
// space is 6008819575 (== (r + 3) / 2), and vertex C virtual indices are on
// stride 2 (== -d % 3).
// 
// We need to find all integers k == 2 + 3z, such that gcd(k, 6008819575) == 1.
// 
// We know:
// prime factorization of 6008819575: 5^2  11^1  17^1  23^1  29^1  41^1  47^1  
//
// We can reject any solutions k that have
// k == 0 mod 25, 0 mod 11, 0 mod 17, 0 mod 23, 0 mod 29, 0 mod 41, 0 mod 47
// 
// We can just generate a count of these and then subtract it from the total
// number of relevant vertices.
//

long gcd(long a, long b) {
    long mod = b % a;
    if(!mod) {
        return a;
    }

    return gcd(mod, a);
}

long solve(long r, long np, long *p) {
    long d = (r + 3) / 2;
    printf("depth: %ld\n", d);

    long pf[32];
    long e[32];

    long nf = 0;
    factor(d, p, np, &nf, pf, e);

    long i;
    printf("prime factorization of %ld: ", d);
    for(i = 0; i < nf; i++) {
        printf("%ld^%ld  ", pf[i], e[i]);
    }
    printf("\n");

    long start = -d + ((3 + ((-d) % 3)) % 3);

    printf("start: %ld\n", start);

    long nsol = 0;
    long count_since_print = 0;
    long done = 0;
    for(i = start; i < start / 2; i += 3) {
        // must check gcd to ensure that this vertex is not collinear with
        // any other vertex reached at a lower depth
        if(gcd(-i, d) == 1) {
            //printf("solution at %ld / %ld\n", d, i);
            nsol += 2;
        }
        done += 1;
        count_since_print += 1;
        if(count_since_print > 10000000) {
            printf("%ld items remaining\n", (start/2 - i) / 3);
            count_since_print = 0;

        }
    }
    printf("number of solutions for r == %ld: %ld\n", r, nsol);
    return nsol;
}

int main() {
    long np;
    long *p;
    primes(100000, &p, &np);
    solve(7, np, p);
    solve(9, np, p);
    solve(11, np, p);
    solve(13, np, p);
    solve(1000001, np, p);
    solve(12017639147, np, p);
}
