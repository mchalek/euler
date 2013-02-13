#include <stdio.h>
#include <stdlib.h>

long countem(short **trans, const short vcount[], int head, 
             int depth, int maxdepth, long tcounts[])
{
    int i;
    long count = 0;
    if(depth == maxdepth) {
        if(NULL != tcounts)
            tcounts[head]++;
        return 1L; // do a total count
    }

    //printf("[%d]\n", vcount[head]);
    for(i = 0; i < vcount[head]; i++) {
      //  printf("%d to %d\n", head, trans[head][i]);
        count += countem(trans, vcount, trans[head][i], 
                         depth + 1, maxdepth, tcounts);
    }

    return count;
}

int main(void)
{
    int i;
    int triplets[1000];
    int ntrip = 0;
    for(i = 0; i < 1000; i++) {
        int j = i % 10;
        j += (i / 10) % 10;
        j += (i / 100);

        if(j < 10) {
            triplets[ntrip++] = i;
        }
    }
    //printf("%d valid triplets.\n", ntrip);

    short **trans = malloc(1000*sizeof(short *));
    short *vcount = calloc(1000, sizeof(short));
    for(i = 0; i < ntrip; i++) {
        int trip = triplets[i];
        int k = trip % 100;
        int j;
        for(j = 0; j < ntrip; j++) {
            vcount[trip] += ((triplets[j]/10) == k);
        }
        trans[trip] = calloc(vcount[trip], sizeof(short));
        vcount[trip] = 0;
        for(j = 0; j < ntrip; j++) {
            if((triplets[j]/10) == k) {
                trans[trip][vcount[trip]++] = triplets[j];
            }
        }
    }

    long *tcounts = calloc(1000, sizeof(long)); // count number of guys ending
                                                // in particular tri-digit
                                                // (left hand side)
    long *scounts = calloc(1000, sizeof(long)); // count number of guys starting
                                                // with particular tri-digit
    for(i = 0; i < ntrip; i++) {
        int trip = triplets[i];

        scounts[trip] = countem(trans, vcount, trip, 0, 8, NULL);
        if(trip > 99)
            countem(trans, vcount, trip, 0, 9, tcounts);
    }

    long count = 0;
    for(i = 0; i < ntrip; i++) {
        int term = triplets[i];

        count += tcounts[term] * scounts[term];
    }

    printf("total count: %ld\n", count);

    return 0;
}
