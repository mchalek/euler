#include <prime.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN_K 2
#define MAX_K 120

void scrub(long *nf, long factors[20], long exponents[20]) {
    int i;
    long new_nf = 0;
    for(i = 0; i < *nf; i++) {
        if(exponents[i]) {
            factors[new_nf] = factors[i];
            exponents[new_nf] = exponents[i];
            new_nf++;
        }
    }

    *nf = new_nf;
}

int doit(int n, int nf, long factors[20], long exponents[20], int *mps,
         int num_items, int sum)
{
    if(!nf) {
        int k = num_items + (n - sum);
        int ret = 0;
        if(k <= MAX_K && k >= 2) {
            if(!mps[k]) {
                printf("mps[%d] == %d\n", k, n);
                mps[k] = n;
                ret = 1;
            }
        }
        return ret;
    }

    long best_k = num_items + 1 + (n - sum);
    if(best_k > MAX_K)
        return 0;

    int ret = 0;

    long i, j, k;
    printf("n == %d, sum == %d, remaining: ", n, sum);
    for(i = 0; i < nf; i++) {
        printf("%d^%d  ", factors[i], exponents[i]);
    }
    printf("\n");

    for(i = 1; i < (1 << nf); i++) {
        // i selects which factors to use in this term
        // now must compute number of different ways to use these
        long ways = 1;
        for(j = 0; j < nf; j++) {
            if(i & (1 << j)) {
                ways *= (1 + exponents[j]);
            }
        }

        printf("%ld ways in total\n", ways);

        for(k = 1; k < ways; k++) {
            int item = 1;

            long new_factors[20];
            memcpy(new_factors, factors, sizeof(new_factors));

            long new_exponents[20];
            memcpy(new_exponents, exponents, sizeof(new_exponents));

            long kk = k;
            for(j = 0; j < nf; j++) {
                if(i & (1 << j)) {
                    int count = kk % (1 + exponents[j]);
                    if(!count)
                        continue;
                    printf("taking %d^%d == %d\n", factors[j], count, 
                            ipow(factors[j], count));
                    new_exponents[j] -= count;
                    item *= ipow(factors[j], count);
                    kk /= exponents[j];
                }
            }

            if(item == 1)
                continue;

            long new_nf = nf;
            scrub(&new_nf, new_factors, new_exponents);

            ret += doit(n, new_nf, new_factors, new_exponents, mps,
                 1 + num_items, sum + item);
        }
    }

    return ret;
}

int main()
{
    long *p, np;
    primes(MAX_K, &p, &np);

    int *mps = calloc(1 + MAX_K, sizeof(int));

    int i = 4;
    int sum = 0;
    int done = 0;
    while(done < (MAX_K - MIN_K + 1) && i < 20) {
        long factors[20];
        long exponents[20];
        long nf;

        factor(i, p, np, &nf, factors, exponents);

        int hits = doit(i, nf, factors, exponents, mps, 0, 0);
        printf("%d hits\n", hits);
        done += hits;
        if(hits) {
            sum += i;
        }
        i++;
    }

    printf("sum: %d\n", sum);

    return 0;
}
