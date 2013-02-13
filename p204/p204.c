#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 100000000

long count_terms(int *powers[], int config[], long prod, int depth)
{

}

int main(void)
{
    int i, j;
    bool isc[101];
    int primes[101];
    int *maxes;
    int **powers;
    int np = 0;

    int *p1, *p2;

    memset(isc, 0, sizeof(isc));

    for(i = 2; i < 100; i++) {
        if(!isc[i]) {
            primes[np++] = i;
            for(j = 2*i; j < 100; j += i)
                isc[j] = true;
        }
    }

    printf("%d primes:\n", np);
    maxes = calloc(np, sizeof(maxes[0]));
    powers = malloc(np*sizeof(powers[0]));
    for(j = 0; j < np; j++) {
        printf("%d: ", primes[j]);

        long prod = primes[j];
        i = 0;
        while(prod < N) {
            prod *= primes[j];
            i++;
        }
        maxes[j] = i;
        powers[j] = calloc(maxes[j],  sizeof(powers[0]));

        powers[j][0] = primes[j];
        for(i = 1; i < maxes[j]; i++) {
            powers[j][i] = powers[j][i-1] * primes[j];
            printf("%d ", powers[j][i]);
        }
        printf("\n");
    }

    return 0;
}
