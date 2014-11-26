#include <stdio.h>
#include <stdint.h>
#include <prime.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define N 50000l
//#define MODULUS 10000000000000000007ul
#define MODULUS 1000000007ul

#define VERBOSE

int main()
{
    long *p;
    long np;
    primes(N, &p, &np);

    printf("np: %ld == Pi(%ld)\n", np, N);

    int pi = 0;

    int64_t i;
    uint64_t *scores = calloc(N+1, sizeof(uint64_t *));
    uint64_t *tmp = malloc((N+1)*sizeof(uint64_t *));

    scores[0] = 1;

    uint64_t S = 6ul; // C(1) == 6
    printf("C(1) == 6, S(1) == 6\n");
    for(i = 2; i <= N; i++) {
        memset(tmp, 0, (MIN(i, np)+1)*sizeof(uint64_t));
        int64_t j; // j is score

        tmp[0] += 5ul*scores[0];
        tmp[0] %= MODULUS;
        for(j = 1; j <= MIN(i, np); j++) {
            tmp[j] += scores[j-1];

            tmp[j] += 5ul*scores[j];
            tmp[j] %= MODULUS;
        }

        uint64_t *tmp2 = scores;
        scores = tmp;
        tmp = tmp2;

        if(p[pi] == i) {
            pi++;
        }

        uint64_t C = 0;
        for(j = 0; j <= pi; j++) {
            C += 6ul*scores[j];
            C %= MODULUS;
        }

        S += C;
#ifdef VERBOSE
        printf("C(%ld) == %ld, S(%ld) == %ld\n", i, C, i, S);
#endif
        S %= MODULUS;
    }

    printf("S(%ld) == %ld\n", N, S);

    return 0;
}
