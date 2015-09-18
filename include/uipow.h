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

    a %= modulus;

    uint64_t result = 1ul;
    uint64_t y = 1ul;
    if(modulus < (1ul << 32)) {
        uint64_t a2n = a; // a^(2^n), starting with n == 0
        do {
            if(b & y) {
                result *= a2n;
                result %= modulus;
                b ^= y;
            }
            a2n *= a2n;
            a2n %= modulus;
            y <<= 1;
        } while(b);
    } else {
        // overflows will happen on uint64_t's
        // use gcc's builtin support for uint128
        __uint128_t result128 = 1ul;
        __uint128_t a2n = a; // a^(2^n) mod modulus, starting with n == 0
        do {
            if(b & y) {
                result128 *= a2n;
                result128 %= modulus;
                b ^= y;
            }
            a2n *= a2n;
            a2n %= modulus;
            y <<= 1;
        } while(b);

        // result is guaranteed to fit in 64 bits
        result = (uint64_t) result128;
    }

    return result;
}

#endif
