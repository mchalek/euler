#include <stdio.h>
#include <stdint.h>
#include <prime.h>
#include <string.h>

#define N 50
#define MODULUS 1000000007

int main()
{
    long *p;
    long np;
    primes(N, &np, &p);

    int pi = 0;

    int64_t i;
    uint32_t *scores = calloc(N+1, sizeof(uint32_t *));
    uint32_t *tmp = malloc((N+1)*sizeof(uint32_t *));

    scores[0] = 1;
    for(i = 1; i <= N; i++) {
        memset(tmp, 0, (N+1)*sizeof(uint32_t));
        int64_t j; // j is score
        for(j = 0; j <= i; j++) {
            if(j)
                tmp[j] += scores[j-1];

            tmp[j] += (5ul*scores[j] % MODULUS);
            tmp[j] %= MODULUS;
        }

        uint64_t *tmp2 = scores;
        scores = tmp;
        tmp = tmp2;

        if(primes[pi] == i) {
            pi++;
        }

        uint64_t C = 0;
        for(j = 0; j <= pi; j++) {
            C += (6ul*scores[j] % MODULUS);
            C %= MODULUS;
        }

        printf("C(%ld) == %ld\n", i, C);
    }

    return 0;
}
