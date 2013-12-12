#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kmbits.h>
#include <stdbool.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

void primes(int N, int **p, int *nprimes) {
    char *isc = calloc(N, sizeof(char));
    int *_p = malloc(N*sizeof(int));
    int np = 0;
    int i;

    for(i = 2; i < N; i++) {
        if(!isc[i]) {
            _p[np++] = i;
            int j;
            for(j = 2*i; j < N; j += i)
                isc[j] = 1;
        }
    }

    *p = realloc(_p, np*sizeof(int));
    *nprimes = np;

    free(isc);
}

void to_bcd(int *p, int np, int *maxdig) {
    int i;
    int max = 0;
    for(i = 0; i < np; i++) {
        int k = 0;
        int bcd = 0;

        while(p[i]) {
            bcd += (p[i] % 10) << (4*k);
            p[i] /= 10;
            k++;
        }
        if(k > max)
            max = k;

        p[i] = bcd;
    }
    *maxdig = max;
}

int to_dec(int bcd) {
    int ret = 0;
    int k = 1;
    while(bcd) {
        int digit = bcd & 0xff;
        ret += digit * k;
        k *= 10;
        bcd >>= 4;
    }

    return ret;
}

bool digits_match(int x, int mask) {
    int k = 0;
    int digits = 0;
    while(mask) {
        if(mask & (1 << k)) {
            int digit = 0xff & (x >> (4*k));
            digits |= 1 << digit;
            mask ^= (1 << k);
        }
        k++;
    }

    return _popcnt(digits) == 1;
}

int condense(int x, int mask) {
    int ret = 0;
    int k = 0;
    int ndig = 0;
    while(mask) {
        if(mask & (1 << k)) {
            int digit = 0xff & (x >> (4*k));
            mask ^= (1 << k);
            ret |= digit << (4*ndig);
            ndig++;
        }
        k++;
    }

    return ret;
}

int main(void) {
    int N = 1000000;
    int *p;
    int np = 0;
    int ndig = 0;

    primes(N, &p, &np);
    to_bcd(p, np, &ndig);

    printf("%d digits\n", ndig);
    printf("last bcd primes:\n");
    int i;
    for(i = 0; i < 10; i++)
        printf("%x\n", p[np-i-1]);

    int z = 0;
    int mask;
    for(mask = 1; mask < (1 << ndig) - 1; mask++) {
        if(_popcnt(mask) < 2)
            continue;

        int j;
        for(j = 0; j < np; j++) {
            if(!digits_match(p[j], mask))
                continue;

            int cond = condense(p[j], (~mask) & 0xffff);

            int cond_dec = to_dec(cond);

            printf("mask %x; digits match: %x\n", mask, p[j]);
            printf("\tcondensed to: %x\n", cond);
            z++;
        }
    }

    printf("z == %d\n", z);

    return 0;
}
