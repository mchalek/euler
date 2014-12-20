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

    uint64_t powers_of_2[64];

    uint64_t result = a;
    int pow = 0;

    uint64_t exp = 1ul;
    do {
        powers_of_2[pow++] = result;
        result *= result;
        result %= modulus;
        exp <<= 1;
    } while(exp < b);

    uint64_t ret = 1;
    pow--;
    exp = 1ul << pow;
    for( ; b ; pow--) {
        int i;
        int n = b / exp;
        for(i = 0; i < n; i++) {
            ret *= powers_of_2[pow];
            ret %= modulus;
        }
        b %= exp;
        exp >>= 1;
    }

    return ret;
}

#endif
