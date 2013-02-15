#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define N 201

typedef struct {
    uint8_t a[16]; // can't handle depth > 15
} avail_t; // size should be 16 bytes, convenient for copy

int main(void)
{
    int8_t counts[N+1];
    avail_t *new, *old;

    int64_t nnew, nold;
    int64_t bufsize;
    int64_t num_assigned;

    memset(counts, -1, sizeof(counts));

    counts[0] = 0;
    counts[1] = 0;
    num_assigned = 1;

    nnew = 0;
    nold = 0;

    bufsize = 10000000;
    new = malloc(bufsize*sizeof(avail_t));
    old = malloc(bufsize*sizeof(avail_t));

    if(!new || !old) {
        printf("memory allocation failure!\n");
        exit(0);
    }
    
    new[0].a[0] = 1;
    nnew = 1;

    int round = 0;

    while(num_assigned < N && round < 20) {
        int i;
        {
            avail_t *tmp = new;
            new = old;
            old = tmp;
        }
        nold = nnew;

        round++;
        
        if(round*nold > bufsize) { // upper bound on size
            bufsize += 10000;

            old = realloc(old, bufsize*sizeof(avail_t));
            new = realloc(new, bufsize*sizeof(avail_t));
        }
        if(!new || !old) {
            fprintf(stderr, "reallocation failed!\n");
            exit(0);
        }

        nnew = 0;
        for(i = 0; i < nold; i++) {
            int j;
            for(j = 0; j < round; j++) {
                if(((int) old[i].a[round-1]) + old[i].a[j] > N)
                    continue;

                new[nnew] = old[i];
                new[nnew].a[round] = new[nnew].a[round-1] + new[nnew].a[j];

                if(-1 == counts[new[nnew].a[round]]) {
                    counts[new[nnew].a[round]] = round;
                    num_assigned++;
                    if(num_assigned == N) {
                        int i;
                        int sum = 0;
                        for(i = 0; i < N; i++) {
                            printf("[%d] %d\n", i, counts[i]);
                            sum += counts[i];
                        }
                        printf("sum: %d\n", sum);

                        exit(0);
                    }
                }
                nnew ++;
            }
        }
    }

    return 0;
}
