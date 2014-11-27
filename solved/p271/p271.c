#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// strategy: recursively assemble solutions to
//   x^3 == 1 mod \prod_i p_i
//   for i == 13 to i == 0

long cube(long x, long m) 
{
    long xmod = x % m;
    long x3 = xmod*xmod*xmod;

    return x3 % m;
}

int main()
{
    //13082761331670030 == 2*3*5*7*11*13*17*19*23*29*31*37*41*43
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};

    int np = sizeof(primes) / sizeof(int);

    long *cur_items = malloc(primes[np-1]*sizeof(long));
    int n_items = 0;
    long *tmp = NULL;

    long i;
    for(i = 1; i < primes[np-1]; i++) {
        if(cube(i, primes[np-1]) == 1) {
            cur_items[n_items++] = i;
        }
    }

    uint64_t cur_modulus = primes[np-1];

    /*
    printf("%d items for m == %ld\n", n_items, cur_modulus);
    for(i = 0; i < n_items; i++)
        printf("%ld ", cur_items[i]);

    printf("\n");
    */

    for(i = np-2; i >= 0; i--) {
        tmp = realloc(tmp, n_items*sizeof(long));
        int tmp_items = n_items;
        memcpy(tmp, cur_items, n_items*sizeof(long));

        cur_items = realloc(cur_items, n_items * primes[i] * sizeof(long));
        n_items = 0;

        int j;
        for(j = 0; j < tmp_items; j++) {
            int k;
            uint64_t test = tmp[j];
            for(k = 0; k < primes[i]; k++) {
                if(cube(test, primes[i]) == 1) {
                    cur_items[n_items++] = test;
                }

                test += cur_modulus;
            }
        }

        cur_modulus *= primes[i];

        /*
        printf("%d items for m == %ld\n", n_items, cur_modulus);
        for(j = 0; j < n_items; j++)
            printf("%ld ", cur_items[j]);

        printf("\n");*/
    }

    uint64_t sum = 0;
    for(i = 0; i < n_items; i++) {
        if(cur_items[i] > 1)
            sum += cur_items[i];
    }

    printf("S(%ld) == %ld\n", cur_modulus, sum);

    return 0;
}

