#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <prime.h>

#define MAX_C 120000l

typedef struct {
    long nf;
    long factors[16];
    long exponents[16];
} factor_t;

bool coprime(factor_t *a, factor_t *b)
{
    int i = 0, j = 0;

    while(i < a->nf && j < b->nf) {
        if(a->factors[i] == b->factors[j])
            return false;

        if(a->factors[i] > b->factors[j])
            j++;
        else
            i++;
    }

    return true;
}

long rad(factor_t *a)
{
    long result = 1;
    int i;
    for(i = 0; i < a->nf; i++)
        result *= a->factors[i];

    return result;
}

int main() 
{
    long np;
    long *p;
    primes(MAX_C, &p, &np);

    long a;

    // do prime factorization of all possible values for (a, b, c)
    factor_t *f = calloc(MAX_C, sizeof(factor_t));
    for(a = 1; a < MAX_C; a++) {
        factor(a, p, np, &f[a].nf, f[a].factors, f[a].exponents);
    }

    printf("Computed all factorizations.\n");

    long num_hits = 0;
    long sum_of_c = 0;

    for(a = 1; a < MAX_C; a++) {
        long b_inc = (a & 1) ? 1 : 2;
        long b;
        for(b = 1 + a; a + b < MAX_C; b += b_inc) {
            if(!coprime(f + a, f + b))
                continue;

            long c = a + b;

            // radicals factor since all are coprime
            if(rad(f+a)*rad(f+b)*rad(f+c) >= c)
                continue;

            printf("ABC hit! (%ld, %ld, %ld)\n", a, b, c);
            num_hits++;
            sum_of_c += c;
        }
    }

    printf("%ld hits for c < %ld; sum_c == %ld\n", num_hits, MAX_C, sum_of_c);

    return 0;
}
