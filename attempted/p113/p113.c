#include <stdio.h>
#include <string.h>

int main()
{
    long incr[10], decr[10];

    int i, j;

    for(i = 0; i < 10; i++) {
        incr[i] = 1;
        decr[i] = 1;
    }

    incr[0] = 0;
    decr[0] = 0;

    for(i = 1; i < 99; i++) {
        long next_incr[10];
        long next_decr[10];

        next_incr[0] = incr[0];
        for(j = 1; j < 10; j++)
            next_incr[j] = incr[j] + incr[j-1];

        next_decr[9] = decr[9];
        for(j = 8; j >= 0; j++)
            next_decr[j] = decr[j] + decr[j+1];

        memcpy(incr, next_incr, sizeof(incr));
        memcpy(decr, next_decr, sizeof(decr));
    }

    long result = 0;
    for(j = 0; j < 10; j++) {
        result += incr[j] + decr[j];
    }

    printf("result: %ld\n", result);

    return 0;
}
