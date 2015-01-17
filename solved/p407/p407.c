#include <prime.h>
#include <stdlib.h>
#include <stdio.h>

//#define N 10
#define N 10000000

int main()
{
    long np, *p;
    primes(N, &p, &np);

    long *solution = malloc((1 + N)*sizeof(long));

    long i;
    for(i = 2; i <= N; i++)
        solution[i] = 1;

    for(i = 2; i <= N; i++) {
        if(!(i % 100000))
            printf("working on i == %ld / %d\n", i, N);
        long factors0[20];
        long exponents0[20];
        long nf0;
        factor(i, p, np, &nf0, factors0, exponents0);

        long factors1[20];
        long exponents1[20];
        long nf1;
        factor(i - 1, p, np, &nf1, factors1, exponents1);

        long factors2[40];
        long exponents2[40];
        long nf2;
        merge_factors(nf0, factors0, exponents0, nf1, factors1, exponents1,
                &nf2, factors2, exponents2);

        long *dd;
        long nd;
        bounded_divisors(i+1, N, nf2, factors2, exponents2, &nd, &dd);

        long j;
        for(j = 0; j < nd; j++) {
            solution[dd[j]] = i;
        }
        
        free(dd);
    }

    long sum = 0;
    for(i = 1; i <= N; i++) {
        //printf("M(%ld) == %ld\n", i, solution[i]);
        sum += solution[i];
    }

    printf("sum: %ld\n", sum);

    return 0;

}
