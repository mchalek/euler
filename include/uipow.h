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

    if((a % modulus) >= (1ul << 32)) {
        fprintf(stderr, "ERROR: %ld %% %ld is too large, cannot exponentiate!\n",
                a, modulus);
        exit(-1);
    }

    a %= modulus;

    uint64_t powers_of_2[64];

    uint64_t result = a;
    int pow = 0;

    while((1l << pow) < b) {
        powers_of_2[pow] = result;
        pow++;
        result *= result;
        result %= modulus;
    }

    uint64_t ret = 1;
    pow--;
    for( ; b ; pow--) {
        int i;
        uint64_t exp = 1l << pow;
        for(i = 0; i < (b / exp); i++) {
            ret *= powers_of_2[pow];
            ret %= modulus;
        }
        b %= exp;
    }

    return ret;
}

#endif
