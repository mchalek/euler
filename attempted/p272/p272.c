#include <prime.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100000000000l
#define FIRST_FOUR (7*9*13*19)
#define MAX_P (((MAX_N + FIRST_FOUR-1) / FIRST_FOUR) + 1000)

long ns = 0;

long count(long init, bool bad_increments[])
{
    long incr = 1;
    long ret = 0;
    long value = init;
    while(value <= MAX_N) {
        ret += value;
        ns++;

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
        return expand(value, choices, max_depth, 0, bad_increments);
    }

    int i;
    long sum = 0;
    for(i = start; i < np3 - max_depth + depth + 1; i++) {
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

    primes(MAX_P, &p, &np);

    long i;

    long count = 0;
    long *p3 = malloc(np*sizeof(long));
    int np3 = 0;
    bool *bad_increments = calloc(1 + MAX_P, sizeof(bool));
    for(i = 0; i < np; i++) {
        // WHY is p[i] % 3 == 1 sufficient!?
        if(p[i] % 3 == 1) {
            p3[np3++] = p[i];
            count++;
            unsigned long j = p[i];
            while(j <= MAX_P) {
                bad_increments[j] = true;
                j += p[i];
            }
        }
        
        // handles special case of 9^2 having 3 solutions
        if(p[i] == 7) {
            p3[np3++] = 9;
            count++;
            unsigned long j = 9;
            while(j <= MAX_P) {
                bad_increments[j] = true;
                j += 9;
            }
        }
    }

    // now recursively build up all numbers with C(n) == 243 by:
    //  - pre-compute a list of valid increments that do not include any of the
    //    3CRU primes
    //  - compute all numbers with 5 distinct 3CRU prime factors, including
    //    repeated factors
    //  - for each of those numbers, iterate over increments until exceeding
    //    10^11
    fprintf(stderr, "%ld primes below %ld have 3 cubed roots of unity\n", count, MAX_P);

    fprintf(stderr, "building...\n");

    long work[5];
    long result = build(1l, work, 5, 0, 0, p3, np3, bad_increments);
    fprintf(stderr, "result: %ld\n", result);
    fprintf(stderr, "%ld hits\n", ns);

    return 0;
}
