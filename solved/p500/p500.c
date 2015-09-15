#include <prime.h>
#include <uipow.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long cost(int index, long p[], int weights[]) {
    long exponent_diff = (1l << (1 + weights[index])) - (1l << weights[index]);

    //fprintf(stderr, "%ld^%ld\n", p[index], exponent_diff);
    return uipow(p[index], exponent_diff, 1ul << 62);
}

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("SYNTAX: %s EXPONENT MODULUS\n", argv[0]);
        exit(1);
    }

    const long EXPONENT = strtol(argv[1], NULL, 10);
    const long MODULUS = strtol(argv[2], NULL, 10);
    long *p;
    long np;

    primes(10000000, &p, &np);

    int *weights = calloc(np, sizeof(int));
    long *current_cost = calloc(np, sizeof(long));
    int i;
    for(i = 0; i < EXPONENT; i++) {
        if(1 == i % 10000)
            printf("completed %d\n", i);

        int j;
        long min_cost = 1l << 62;
        long best_index = -1;
        for(j = 0; j < np; j++) {
            long c = current_cost[j];

            if(!c) {
                c = cost(j, p, weights);
                current_cost[j] = c;
            }

            if(c < min_cost) {
                min_cost = c;
                best_index = j;
            }

            if(!weights[j])
                break;
        }
        
        weights[best_index]++;
        current_cost[best_index] = 0l;
    }

    long result = 1l;
    for(i = 0; i < np; i++) {
        if(!weights[i])
            break;

        //printf("weight[%ld] == %d\n", p[i], weights[i]);

        int j;
        int k = (1l << weights[i]) - 1;
        for(j = 0; j < k; j++) {
            result *= p[i];
            result %= MODULUS;
        }
    }

    printf("result: %ld\n", result);


    return 0;
}
