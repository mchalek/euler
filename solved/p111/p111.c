#include <prime.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define PMIN 1000000000l
#define PMAX 9999999999l

// this is probably pretty dumb.  I actually construct all 10-digit primes,
// and compute the max digit counts over all of them.  I assume it's faster
// to start out assuming 10 repeated digits, then try 9, and so on until you
// find something that works, and do this for all digits.  That way you only
// need the ability to test for primality among 10 digit numbers, you don't
// need to construct the complete set of numbers.  But whatever, I optimized
// the hell out of my prime sieve and I can generate all of them in about a
// minute.

void get_counts(long x, int counts[]) {
    memset(counts, 0, 10*sizeof(int));
    while(x) {
        counts[x % 10]++;
        x /= 10;
    }
}

void update_maxes(long x, int counts[], int maxes[], uint64_t sums[]) {
    int i;
    for(i = 0; i < 10; i++) {
        if(counts[i] < maxes[i])
            continue;

        if(counts[i] == maxes[i])
            sums[i] += x;

        if(counts[i] > maxes[i]) {
            maxes[i] = counts[i];
            sums[i] = x;
        }
    }
}

int main(void)
{
    // first compute all 10-digit primes
    long *p, np;
    primes(PMAX, &p, &np);
    
    int max_counts[10];
    memset(max_counts, 0, sizeof(max_counts));

    uint64_t max_sums[10];
    memset(max_sums, 0, sizeof(max_sums));

    int counts[10];

    long i;
    for(i = 0; i < np; i++) {
        if(p[i] < PMIN)
            continue;

        if(p[i] > PMAX)
            break;

        get_counts(p[i], counts);
        update_maxes(p[i], counts, max_counts, max_sums);
    }

    uint64_t result = 0;
    for(i = 0; i < 10; i++)
        result += max_sums[i];

    printf("result: %ld\n", result);

    return 0;
}
