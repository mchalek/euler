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

void to_bcd(int *p, int np, int *masks, int *maxdig) {
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

        masks[i] = (1 << k) - 1;

        p[i] = bcd;
    }
    *maxdig = max;
}

int to_dec(int bcd) {
    int ret = 0;
    int k = 1;
    while(bcd) {
        int digit = bcd & 0xf;
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
            int digit = 0xf & (x >> (4*k));
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
        if(1 & (mask >> k)) {
            int digit = 0xf & (x >> (4*k));
            mask ^= (1 << k);
            ret |= digit << (4*ndig);
            ndig++;
        }
        k++;
    }

    return ret;
}

int expand0(int mask, int x) {
    int ret = 0;
    int k = 0;
    while(k < 7) {
        if(!(1 & (mask >> k))) {
            int digit = x % 10;
            x /= 10;

            ret |= digit << (4*k);
        }
        k++;
    }

    return ret;
}

int insert(int mask, int x, int dupe) {
    int k = 0;
    while(k < 7) {
        if(1 & (mask >> k)) {
            x |= dupe << (4*k);
        }
        k++;
    }

    return x;
}

void expand(int mask, int x, int hits[]) {
    int ret = expand0(mask, x);
    int i;

    for(i = 0; i < 10; i++) {
        hits[i] = insert(mask, ret, i);
    }
}

int main(void) {
    int N = 1000000;
    int *p;
    int np = 0;
    int ndig = 0;

    primes(N, &p, &np);
    int *masks = calloc(np, sizeof(int));
    to_bcd(p, np, masks, &ndig);

    int *dc = malloc(N * sizeof(int));

    int mask;
    for(mask = 1; mask < (1 << ndig) - 1; mask++) {
        if(_popcnt(mask) < 2)
            continue;

        memset(dc, 0, N*sizeof(int));

        int j;
        for(j = 0; j < np; j++) {
            if((mask & masks[j]) != mask)
                continue;

            if(!digits_match(p[j], mask))
                continue;

            int cond = condense(p[j], (~mask) & masks[j]);
            int cond_dec = to_dec(cond);

            dc[cond_dec]++;
        }

        for(j = 0; j < N; j++) {
            if(dc[j] == 8) {
                int hits[10];
                expand(mask, j, hits);
                int k;
                for(k = 0; k < 10; k++) {
                    int z;
                    for(z = 0; z < np; z++) {
                        if(hits[k] == p[z])
                            break;
                    }
                    printf("%x (%d)", hits[k], z < np);
                    if(k < 9)
                        printf(",");
                }
                printf("\n");
            }
        }
    }

    return 0;
}
