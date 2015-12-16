#include <stdio.h>
#include <bitarray.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#if 0

#define p 19
#define q 37

#else

#define p 1009
#define q 3643

#endif

//#define __DEBUG__

#define n (p*q)
#define phi ((p-1)*(q-1))

int _find_order(const long m, long x, int order, bitarray_t *ba) 
{
    while(x != 1) {
        //set_bit(x, ba);
        x *= m;
        x %= n;
        order += 1;
    }

    return order;
}

int find_order(long m, bitarray_t *ba)
{
    if(m == 0 || m == 1)
        return 1;

    clear(ba);
    return _find_order(m, m, 1, ba);
}

void sieve(int order, int unconcealed_count[])
{
    int k;
    for(k = 1 + order; k < phi; k += order) {
        unconcealed_count[k] += 1;
    }
}

int test(int e) {
    // make sure that gcd(e, phi) == 1
    
    int gcd = 2;
    while(gcd < (phi/2)) {
        if(!(e % gcd) && !(phi % gcd))
            return gcd;

        gcd += 1;
    }

    return 1;
}

int main(void) {
    int m;

    int *unconcealed_count = calloc(phi, sizeof(int));
    bitarray_t bt;
    bitarray_init(n, &bt);

    fprintf(stderr, "%6.3f%% complete\b\b\b\b\b\b\b\b\b\b", 0.0); 
    for(m = 0; m < n; m++) {
        if(!(m % p))
            continue;

        if(!(m % q))
            continue;

        int order = find_order(m, &bt);

        sieve(order, unconcealed_count);
#ifdef __DEBUG__
        fprintf(stderr, "order(%d): %d\n", m, order);
#else
        if(!(m % 500)) {
            fprintf(stderr, "\b\b\b\b\b\b\b%6.3f", 100*((double) m) / n);
        }
#endif
    }

    int min_count = n;
    int e;
    for(e = 2; e < phi; e++) {
        //printf("unconcealed_count[181]: %d\n", unconcealed_count[e]);
        if(unconcealed_count[e] < min_count && test(e) == 1)
            min_count = unconcealed_count[e];
    }

    printf("smallest number of unconcealed messages: %d\n", min_count);
    
    int sum_e = 0;
    for(e = 2; e < phi; e++) {
        if(unconcealed_count[e] == min_count) {
            printf("e == %4d achieves minimum unconcealed count\n", e);
            sum_e += e;
        }
    }
    printf("result: %d\n", sum_e);

    return 0;
}
