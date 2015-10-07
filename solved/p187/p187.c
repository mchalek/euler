#include <prime.h>
#include <stdio.h>

#define NMAX 100000000

int main(void) {
    long np, *p;
    primes(NMAX, &p, &np);

    long lastptr = np-1;

    int i;
    long result = 0;

    for(i = 0; i < np; i++) {
        long qmax = NMAX / p[i];

        while(p[lastptr] > qmax) {
            lastptr--;
        }

        if(lastptr < i)
            break;

        result += lastptr - i + 1;
    }

    printf("result: %ld\n", result);
    return 0;
}
