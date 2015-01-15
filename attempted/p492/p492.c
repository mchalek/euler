#include <prime.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define X 1000000000l
#define Y 1000l
#define Z 1000000000000000l
//#define Z 1000l

#define WORK_SIZE (((X + Y + 63) / 64) * sizeof(uint64_t))

#define NEXT(a) (6*(a)*(a) + 10*(a) + 3) // == (3a + 3)(2a + 1) + a

bool check_and_update(long idx, uint64_t *work) {
    uint64_t word = idx / 64;
    uint64_t bit = 1ul << (idx % 64);

    bool ret = work[word] & bit;

    work[word] |= bit;

    return ret;
}

long B(long p, uint64_t *work) {
    memset(work, 0, WORK_SIZE);

    long a = 1;
    long i = 0;

    while(!check_and_update(a, work)) {
        i++;
        a = NEXT(a) % p;
    }

    long cycle_len = i;
    long cycle_start = a;

    long z = Z;
    a = 1;
    while(a != cycle_start) {
        cycle_len--;
        z--;
        a = NEXT(a) % p;
    }

    printf("cycle len for p == %ld is %ld (repeats at %ld)\n", p, cycle_len, cycle_start);

    z %= cycle_len;

    a = cycle_start;
    for(i = 0; i < z - 1; i++) {
        a = NEXT(a) % p;
    }

    printf("a_%ld for p == %ld is %ld\n", Z, p, a);
    return a;
}

int main()
{
    long *p, np;
    primes(100000, &p, &np);

    long i;
    uint64_t *work = malloc(WORK_SIZE);
    long result = 0;
    for(i = X; i <= X+Y; i++) {
        if(isprime(i, p, np)) {
            printf("%ld is prime\n", i);
            long Bi = B(i, work);
            result += Bi;
        } else {
            //printf("%ld is not prime\n", i);
        }
    }
    printf("B(%ld, %ld, %ld) == %ld\n", X, Y, Z, result);

    free(p);

    return 0;
}
