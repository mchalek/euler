#include <stdio.h>
#include <string.h>

int main()
{
    long incr[10], decr[10];

    int i, j, k;

    for(i = 1; i < 10; i++) {
        incr[i] = 1;
        decr[i] = 1;
    }

    // first digit cannot be zero for either
    incr[0] = 0;
    decr[0] = 0;

    long result = 9; // all single digits are valid
    for(i = 1; i < 100; i++) {
        long next_incr[10];
        long next_decr[10];

        next_incr[0] = incr[0];
        for(j = 1; j < 10; j++) {
            next_incr[j] = 0;
            for(k = 0; k <= j; k++)
                next_incr[j] += incr[k];
        }

        next_decr[9] = decr[9];
        for(j = 8; j >= 0; j--) {
            next_decr[j] = 0;
            for(k = j; k < 10; k++)
                next_decr[j] += decr[k];
        }

        memcpy(incr, next_incr, sizeof(incr));
        memcpy(decr, next_decr, sizeof(decr));

        for(j = 0; j < 10; j++) {
            result += incr[j] + decr[j];
        }

        result -= 9; // remove numbers that are both bouncy and non-bouncy, i.e.
                     // numbers that are all the same digit
    }


    printf("result: %ld\n", result);

    return 0;
}
