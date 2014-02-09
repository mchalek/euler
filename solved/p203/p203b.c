#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void get_primes(int max, long **p_p, int *np_p) {
    bool *iscomp = calloc((max+1), sizeof(bool));
    int np = 0;
    long *p = malloc((max+1)*sizeof(long));
    
    int test;
    for(test = 2; test <= max; test++) {
        if(!iscomp[test]) {
            p[np++] = test;
            int k;
            for(k = test*2; k <= max; k += test)
                iscomp[k] = true;
        }
    }

    free(iscomp);
    *p_p = realloc(p, np*sizeof(long));
    *np_p = np;
}

long sum_squarefree(long *values, int n, long *sqprimes, int num_primes) {
    int i;
    long ret = 0;
    for(i = 0; i < n; i++) {
        long value = values[i];
        int j;
        bool sqfree = true;
        for(j = 0; j < num_primes; j++) {
            if(sqprimes[j] > value)
                break;
            
            if(!(value % sqprimes[j])) {
                sqfree = false;
                break;
            }
        }
        ret += sqfree ? value : 0;
    }

    return ret;
}

int main(void) {
    int nalloc = 1000;
    long *values = malloc(nalloc*sizeof(long));
    char buf[256];
    int n = 0;
    long max = -1;
    while(NULL != fgets(buf, sizeof(buf), stdin)) {
        values[n] = strtol(buf, NULL, 10);
        if(values[n] > max) {
            max = values[n];
        }
        n++;
    }

    int max_prime = (int) ceil(sqrt(max));
    while(((long) max_prime) * ((long) max_prime) < max)
        max_prime++;

    long *sqprimes;
    int num_primes;
    get_primes(max_prime, &sqprimes, &num_primes);

    int i;
    for(i = 0; i < num_primes; i++)
        sqprimes[i] *= sqprimes[i];

    long result = sum_squarefree(values, n, sqprimes, num_primes);

    printf("result: %ld\n", result);

    return 0;
}
