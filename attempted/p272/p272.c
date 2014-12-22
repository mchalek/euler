#include <prime.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define MAX_N 100000000000l
#define MAX_N 30000000l
//#define MAX_N 10000000l
#define FIRST_FOUR (7*13*19*31ul)
#define MAX_P (((MAX_N + FIRST_FOUR-1) / FIRST_FOUR) + 1000)
//#define MAX_P 1865706ul
//#define MAX_P 2000000ul


void brute(int num_roots[], long *p, long np)
{
    long i;
    long sum = 0, n = 0;
    for(i = 2; i <= MAX_N; i++) {
        long nf;
        long pfactors[20];
        long exponents[20];

        factor(i, p, np, &nf, pfactors, exponents);

        int j;
        long count = 1;
        if(nf < 5)
            continue;
        for(j = 0; j < nf; j++) {
            if(pfactors[j] > MAX_P)
                continue;
            long this_prime = 1 + num_roots[pfactors[j]];

            count *= this_prime;
        }

        if(count == 243) {
            sum += i;
            n++;
        }
    }

    printf("via brute force: %ld items, sum to %ld\n", n, sum);
}

long ns = 0;

long count(long init, bool bad_increments[])
{
    long incr = 1;
    long ret = 0;
    long value = init;
    while(value <= MAX_N) {
        ret += value;
        ns++;
        //if(value < 1000000000) {
            //printf("Hit on %ld!\n", value);
        //}
        //printf("%ld\n", value);

        incr++;
        value += init;

        while(bad_increments[incr] && value <= MAX_N) {
            incr++;
            value += init;
        }
    }

    return ret;
}

long expand(long init, long choices[], int max_depth, int depth, bool bad_increments[])
{
    if(max_depth == depth)
        return count(init, bad_increments);

    long value = init;
    long sum = 0;
    while(value <= MAX_N) {
        sum += expand(value, choices, max_depth, 1 + depth, bad_increments);

        value *= choices[depth];
    }

    return sum;
}

long build(long value, long choices[], int max_depth, int depth, int start, long *p3, long np3, bool bad_increments[])
{
    if(depth == max_depth) {
        return expand(value, choices, 5, 0, bad_increments);
    }

    int i;
    long sum = 0;
    //for(i = start; i < np3 - max_depth + depth + 1; i++) {
    for(i = start; i < np3; i++) {
        long nextval = value * p3[i];
        if(nextval > MAX_N)
            break;

        choices[depth] = p3[i];

        sum += build(nextval, choices, max_depth, 1 + depth, i + 1, p3, np3, bad_increments);
    }

    return sum;
}

int main()
{
    long np;
    long *p;

    long *p3;

    primes(MAX_P, &p, &np);

    int *num_roots = calloc(MAX_P+1, sizeof(int));
    uint64_t i;

    for(i = 2; i < MAX_P; i++) {
        if(!(i % 10000))
            fprintf(stderr, "doing i == %ld\n", i);
        uint64_t test = i*i + i + 1;
        long nf;
        long pfactors[20];
        long exponents[20];
        factor(test, p, np, &nf, pfactors, exponents);

        int j;
        for(j = 0; j < nf; j++) {
            if(pfactors[j] > (long) i && pfactors[j] <= (long) MAX_P) {
                //printf("%ld^3 == 1 mod %ld\n", i, pfactors[j]);
                num_roots[pfactors[j]]++;
            }
        }
    }

    long count = 0;
    p3 = malloc(np*sizeof(long));
    int np3 = 0;
    bool *bad_increments = calloc(1 + MAX_P, sizeof(bool));
    for(i = 2; i <= MAX_P; i++) {
        if(num_roots[i] == 2) {
            p3[np3++] = i;
            count++;
            unsigned long j = i;
            while(j <= MAX_P) {
                bad_increments[j] = true;
                j += i;
            }
        }
    }

    brute(num_roots, p, np);

    // now recursively build up all numbers with C(n) == 243 by:
    //  - pre-compute a list of valid increments that do not include any of the
    //    3CRU primes
    //  - compute all numbers with 5 distinct 3CRU prime factors, including
    //    repeated factors
    //  - for each of those numbers, iterate over increments until exceeding
    //    10^11
    fprintf(stderr, "%ld primes below %ld have 3 cubed roots of unity\n", count, MAX_P);

    fprintf(stderr, "building...\n");

    long choices[5];
    //printf("%ld products of 5 3CRU primes\n", build(1l, choices, 5, 0, 0, p3, np3, bad_increments));
    fprintf(stderr, "result: %ld\n", build(1l, choices, 5, 0, 0, p3, np3, bad_increments));
    fprintf(stderr, "%ld hits\n", ns);

    return 0;
}
