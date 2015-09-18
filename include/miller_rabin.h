#ifndef __MILLER_RABIN_H
#define __MILLER_RABIN_H
#include <uipow.h>
#include <kmbits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MIN(a, b) (((a) > (b)) ? (b) : (a))

#ifndef __KM_RAND_H
inline int rand_int(int a, int b) {
    int x = rand() % (b-a);

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
        int a = rand_int(2, MIN(RAND_MAX, n-1));

        long x = uipow(a, d, n);

        if(x == 1 || x == (n-1))
            continue;

        int j;
        possibly_prime = false;
        for(j = 0; j < r-1; j++) {
            x *= x;
            x %= n;

            if(x == 1) {
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
