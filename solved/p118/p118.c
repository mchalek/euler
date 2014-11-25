#include <stdio.h>
#include <string.h>
#include <prime.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t mask(long n)
{
    uint16_t ret = 0;
    while(n) {
        int dig = n % 10;
        n /= 10;
        if(!dig || (ret & (1 << (dig-1))))
            return 0xffff;

        ret |= (1 << (dig-1));
    }

    return ret;
}

uint64_t count(uint16_t mask, uint16_t min, uint64_t counts[], uint64_t total) {
    if(mask == 0x1ff) {
        return total;
    }

    uint16_t next;
    uint64_t result = 0;
    for(next = min; next < 512; next++) {
        if(!counts[next])
            continue;

        if(mask & next)
            continue;

        uint64_t next_total = total ? total*counts[next] : counts[next];

        result += count(mask | next, next + 1, counts, next_total);
    }

    return result;
}

int main(void)
{
    long *p;
    long np;

    uint64_t counts[512];
    memset(counts, 0, sizeof(counts));
    primes(100000000, &p, &np);
    printf("found primes.  now checking.\n");
    fflush(stdout);

    long i;
    for(i = 0; i < np; i++) {
        int m = mask(p[i]);
        if(m != 0xffff) {
            counts[m]++;
        }
    }

    uint64_t result = count(0, 0, counts, 0);

    printf("sum: %ld\n", result);

    return 0;
}
