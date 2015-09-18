#ifndef __IPOW_H
#define __IPOW_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static inline uint64_t uipow(uint64_t a, uint64_t b, uint64_t modulus)
{
    if(!a)
        return 0ul;

    if(a == 1 || b == 0)
        return 1ul;

    if(b == 1)
        return a % modulus;

    if((a % modulus) >= (1ul << 32)) {
        fprintf(stderr, "ERROR: %ld %% %ld is too large, cannot exponentiate!\n",
                a, modulus);
        exit(-1);
    }

    a %= modulus;

    uint64_t a2n = a; // a^(2^n), starting with n == 0
    uint64_t y = 1ul;
    uint64_t result = 1ul;
    do {
        if(b & y) {
            result *= a2n;
            result %= modulus;
            b ^= exp;
        }
        a2n *= a2n;
        a2n %= modulus;
        y <<= 1;
    } while(b);

    return result;
}

#endif
