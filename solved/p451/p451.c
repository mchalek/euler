#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX 20000000ul
//#define MAX 101ul

void factorize(uint64_t n, uint64_t factors[], int powers[], int *nfact, uint64_t primes[], int np)
{
    uint64_t nn = n;
    int i;
    int k = 0;
    for(i = 0; i < np && 1ul < n; i++) {
        uint64_t p = primes[i];

        if(!(n % p)) {
            int l = 0;
            do {
                n /= p;
                l++;
            } while(!(n % p));
            factors[k] = p;
            powers[k] = l;
            k++;
        }
    }

    if(n != 1ul) {
        printf("failed to factor %ld\n", nn);
        exit(0);
    } else {
        //printf("successfully factored %ld\n", nn);
    }
    *nfact = k;
}

void mkprimes(int max_n, uint64_t **primes, int *np)
{
    bool *iscomp = calloc(1 + max_n, sizeof(bool));

    *primes = malloc((1 + max_n)*sizeof(uint64_t));

    int i;
    *np = 0;

    for(i = 2; i <= max_n; i++) {
        if(!iscomp[i]) {
            (*primes)[*np] = i;
            (*np)++;
            int j = 2*i;
            while(j <= max_n) {
                iscomp[j] = true;
                j += i;
            }
        }
    }

    *primes = realloc(*primes, (*np)*sizeof(uint64_t));
}

void setem(uint64_t cur, uint64_t min, uint64_t *items, uint64_t factors[], int powers[], int nfact, uint64_t cumprod);
void setem(uint64_t cur, uint64_t min, uint64_t *items, uint64_t factors[], int powers[], int nfact, uint64_t cumprod) {
    if(cur > MAX)
        return;

    if(!nfact) {
        items[cur] = min;
        return;
    }

    uint64_t fact = factors[nfact-1];
    int i;
    uint64_t new_cur = cur;
    uint64_t rem_prod = cumprod;
    for(i = 0; i < powers[nfact-1]; i++)
        rem_prod /= fact;

    uint64_t min_cur = (1+min) / rem_prod;
    
    for(i = 0; i <= powers[nfact-1]; i++) {
        if(new_cur > MAX)
            break;
        if(new_cur > min_cur)
            setem(new_cur, min, items, factors, powers, nfact-1, rem_prod);
        new_cur *= fact;
    }

    return;
}

int main(void) {
    uint64_t *primes;
    int nprimes;
    mkprimes(MAX, &primes, &nprimes);

    uint64_t *zz = calloc(20000001, sizeof(uint64_t));

    uint64_t z;

    uint64_t factors[20];
    int powers[20];
    int nfact;

    for(z = 3; z <= MAX; z++) {
        if(!(z % 100000)) {
            printf("z == %ld\n", z);
        }
        //printf("considering %ld\n", z);
        uint64_t z2 = z*z-1ul;

        //printf("relevant: %ld\n", z2);

        factorize(z2, factors, powers, &nfact, primes, nprimes);

        //printf("%ld == ", z2);
        //int q = 0;
        //for(q = 0; q < nfact; q++) {
            //printf("%ld^%d", factors[q], powers[q]); 
            //if(q + 1 < nfact)
                //printf(" * ");
        //}

        //printf("\n");

        //printf("setting...");
        fflush(stdout);
        setem(1ul, z, zz, factors, powers, nfact, z2);
        //printf("done.\n");
    }

    uint64_t sum = 0ul;
    for(z = 3; z <= MAX; z++) {
        uint64_t I = zz[z] ? zz[z] : 1ul;
        printf("I(%ld) == %ld\n", z, I);
        sum += I;
    }

    printf("SUM: %ld\n", sum);

    free(zz);

    return 0;
}
