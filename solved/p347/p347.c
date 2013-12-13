#include <stdlib.h>
#include <stdio.h>
#include <prime.h>

#define N 10000000
//#define N 100

int main(void)
{
    int i, j, k, *p;
    int **table;
    int *ntable;
    long tmp;
    int pqmax;
    long pqtest;
    int pm, qn;
    long SN;

    primes(N/2, &p, &k);

    table = malloc(k*sizeof(int *));
    ntable = malloc(k*sizeof(int));

    // first build table of powers of each prime less than N/2
    for(i = 0; i < k; i++) {
        ntable[i] = 0;
        tmp = 1;
        do {
            tmp *= p[i];
            ntable[i]++;
        } while(tmp*p[i] < N/2);

        table[i] = malloc(ntable[i]*sizeof(int));
        
        table[i][0] = p[i];
        for(j = 1; j < ntable[i]; j++) {
            table[i][j] = table[i][j-1] * p[i];
        }
    }

    // now loop over all pairs of primes, finding the largest
    // products within the bound
    SN = 0;
    for(i = 0; i < k; i++) {
        for(j = i+1; j < k && ((long) p[i])*p[j] < N; j++) {
            pqmax = 0;
            pqtest = -1;
            for(pm = 0; pm < ntable[i]; pm++) {
                for(qn = ntable[j]-1; qn >= 0; qn--) {
                    if((pqtest=((long) table[i][pm])*table[j][qn]) <= N)
                        break;
                }
                pqmax = (pqmax < pqtest && pqtest <= N) ? pqtest : pqmax;
            }
            //printf("M(%d, %d, %d) == %d\n", p[i], p[j], N, pqmax);
            SN += pqmax;
        }
    }

    printf("S(%d) == %ld\n", N, SN);
    return 0;
}
