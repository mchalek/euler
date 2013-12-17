#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int N = 0;

void mark_primes(int p, int *iscomp, int (*my_primes)[7], int nprimes[])
{
    int i;
    for(i = p; i <= N; i += p) {
        my_primes[i][nprimes[i]++] = p;
        iscomp[i] = 1;
    }

    iscomp[p] = 0;
}

void subtract_noncoprime(int *counts, int p, int my_primes[], int nprimes, char work[])
{
    int i, j;
    memset(work, 0, (N+1)*sizeof(char));
    //printf("primes (%d): ", p);
    for(i = 0; i < nprimes; i++) {
        int q = my_primes[i];
        //printf("%d ", q);
        for(j = p; j <= N; j += q) {
            if(!work[j] && 3*p > j && 2*p < j)
                counts[j]++;
            work[j] = 1;
        }
    }
}

int max_allowed(int x) {
    int i;
    int ret = 0;
    for(i = x/3; i < (x+1)/2; i++) {
        ret += (3*i > x && 2*i < x);
    }

    return ret;
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("syntax: %s N\n", argv[0]);
        exit(1);
    }
    N = atoi(argv[1]);
    int i;

    char *work = malloc((N+1)*sizeof(char));
    int (*my_primes)[7] = calloc((N+1), sizeof(int [7]));
    int *nprimes = calloc((N+1), sizeof(int));
    int *iscomp = calloc((N+1), sizeof(int));

    int *counts = calloc((N+1), sizeof(int));

    long total = 0;

    for(i = 2; i <= N; i++) {
        if(!iscomp[i]) {
            mark_primes(i, iscomp, my_primes, nprimes);
        } 
        subtract_noncoprime(counts, i, my_primes[i], nprimes[i], work);

        total += max_allowed(i) - counts[i];
    }
    
    printf("total: %ld\n", total);

    free(my_primes);
    free(nprimes);
    free(iscomp);
    free(counts);

    return 0;
}
