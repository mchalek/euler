#include <stdio.h>
#include <prime.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    long np, *p;
    primes(5000, &p, &np);

    long max = 0;
    int i;
    for(i = 0; i < np; i++)
        max += p[i];
    max++;

    long *ways = calloc(max, sizeof(long));
    long *prev = malloc(max * sizeof(long));

    ways[0] = 1;

    for(i = 0; i < np; i++) {
        memcpy(prev, ways, max*sizeof(long));

        int j;
        for(j = 0; j < max - p[i]; j++) {
            ways[j + p[i]] += prev[j];
            ways[j + p[i]] %= 10000000000000000l;
        }
    }

    long result = 0;
    for(i = 2; i < max; i++) {
        if(isprime(i, p, np)) {
            result += ways[i];
            result %= 10000000000000000l;
        }
    }

    printf("result: %ld\n", result);

    return 0;
}
