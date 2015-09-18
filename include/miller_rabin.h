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
    if(!(n & 1))
        return false;

    uint64_t d = n-1;
    int r = _trailz(d);
    d >>= r;

    int i;
    bool possibly_prime = true;
    for(i = 0; i < 5 && possibly_prime; i++) {
        uint64_t a = rand_int(2, MIN(RAND_MAX, n-1));

        uint64_t x = uipow(a, d, n);
        
        if(x == 1ul || x == (n-1))
            continue;

        int j;
        possibly_prime = false;
        for(j = 0; j < r-1; j++) {
            // use uipow for the overflow safety it provides
            x = uipow(x, 2, n);

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
