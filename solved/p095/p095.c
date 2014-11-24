#include <prime.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long N = 2000;
    long *p;
    long np;

    primes(N, &p, &np);

    long i;
    long nf;
    long factors[20];
    long exponents[20];

    long *pdsums = calloc(1000000, sizeof(long));

    for(i = 1; i < 1000000; i++) {
        factor(i, p, np, &nf, factors, exponents);

        long *pd;
        long npd;
        divisors(nf, factors, exponents, &npd, &pd);

        long j;
        long pdsum = 0;
        for(j = 0; j < npd-1; j++) {
            pdsum += pd[j];
        }

        pdsums[i] = pdsum; 

        free(pd);
    }

    int *chain_len = calloc(1000000, sizeof(int));

    long max_len = 0;
    long smallest_value = -1;

    long *chain = malloc(1000*sizeof(long));

    for(i = 1; i < 1000000; i++) {
        if(chain_len[i])
            continue;

        long item = i;

        chain[0] = i;
        bool stop = false;
        do {
            chain_len[i]++;
            item = pdsums[item];
            if(item > 999999) {
                break;
            }
            int j;
            for(j = 0; j < chain_len[i]; j++) {
                stop |= chain[j] == item;
            }
            chain[chain_len[i]] = item;
        } while(!stop);

        bool amicable = item == i;
        long j;

        if(amicable) {
            printf("amicable chain: ");
            for(j = 0; j < chain_len[i]; j++) {
                printf("%ld ", chain[j]);
            }
            printf("\n");

            if(chain_len[i] > max_len) {
                max_len = chain_len[i];
                smallest_value = i;
            }
        }
    }

    printf("solution: %ld\n", smallest_value);

    return 0;
}
