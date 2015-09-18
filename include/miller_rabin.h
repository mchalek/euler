#ifndef __MILLER_RABIN_H
#define __MILLER_RABIN_H
#include <uipow.h>
#include <kmbits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

#ifndef __KM_RAND_H
inline long rand_int(long a, long b) {
    long x = rand() % (b-a);

    return a + x;
}
#endif

bool mr_isprime(uint64_t n) {
    bool doit = (n == 5230182401);
    if(!(n & 1))
        return false;

    uint64_t d = n-1;
    int r = _trailz(d);
    d >>= r;

    printf("%ld == 2^%d %ld\n", n-1, r, d);

    int i;
    bool possibly_prime = true;
    for(i = 0; i < 5 && possibly_prime; i++) {
        uint64_t a = rand_int(2, MIN(RAND_MAX, n-1));

        uint64_t x = uipow(a, d, n);
        
        uint64_t xc = x;

        if(doit) {
            printf("chose a == %ld\n", a);
            printf("%ld^%ld == %ld mod %ld\n", a, d, x, n);
        }


        if(x == 1ul || x == (n-1))
            continue;

        int j;
        possibly_prime = false;
        for(j = 0; j < r-1; j++) {
            x *= x;
            x %= n;

            if(doit)
                printf("%ld^(2^%d) == %ld mod %ld\n", xc, j+1, x, n);

            if(x == 1ul) {
                possibly_prime = false;
                break;
            }

            if(x == (n-1)) {
                possibly_prime = true;
                break;
            }
        }
    }

    return possibly_prime;
}

#endif
