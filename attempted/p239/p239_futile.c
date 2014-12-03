#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <prime.h>

#define N 50

long count(int depth, int primes[], int num_primes, int target,
           int num_comp_filled, int num_prime_filled, bool prime_filled[],
           int num_foolish)
{
    if(depth == num_primes) {
        return 1l;
    }

    int needed_foolish = target - num_foolish;
    int num_after_this = num_primes - depth - 1;

    //printf("at depth %d, needed: %d, num_after: %d\n", depth, needed_foolish, num_after_this);

    // make sure target is possible down this path
    if(needed_foolish > 1 + num_after_this)
        return 0l;

    int p = primes[depth];
    long ret = 0l;

    int i;
    for(i = 0; i < num_primes; i++) {
        if(i == depth && !prime_filled[p] && needed_foolish <= num_after_this) {
            // it's okay to place this prime in its natural position
            prime_filled[p] = true;

            ret += count(1 + depth, primes, num_primes, target,
                    num_comp_filled, 1 + num_prime_filled, prime_filled,
                    num_foolish);

            prime_filled[p] = false;
        } else
            continue;

        if(needed_foolish) {
            prime_filled[i] = true;
            ret += count(1 + depth, primes, num_primes, target,
                    num_comp_filled, 1 + num_prime_filled, prime_filled,
                    1 + num_foolish);
            prime_filled[i] = false;
        }
    }

    ret += (N - num_primes - num_comp_filled) *
            count(1 + depth, primes, num_primes, target,
                1 + num_comp_filled, num_prime_filled, prime_filled,
                1 + num_foolish);

    return ret;
}

int main()
{
    long lnp, *lp;
    primes(N, &lp, &lnp);
    int np = (int) lnp;
    int *p = malloc(lnp*sizeof(int));

    int i;
    for(i = 0; i < np; i++)
        p[i] = lp[i];

    free(lp);

    printf("%d primes < %d\n", np, N);

    bool pf[1+N];
    memset(pf, 0, sizeof(pf));

    long c = count(0, p, np, np-2, 0, 0, pf, 0);

    printf("%ld ways to derange the primes\n", c);

    return 0;
}
