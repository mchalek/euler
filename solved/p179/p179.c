#include <stdio.h>
#include <stdlib.h>

#define N 10000000

int main()
{
    long *dcount = calloc(N, sizeof(long));

    long i;
    for(i = 1; i < N; i++) {
        long j = i;
        while(j < N) {
            dcount[j]++;
            j += i;
        }
    }

    for(i = 2; i < N - 1; i++) {
        if(dcount[i] == dcount[1 + i]) {
            printf("%ld\t%ld\t%ld\n", i, 1 + i, dcount[i]);
        }
    }

    return 0;
}
