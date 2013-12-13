#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COINS 10000
#define TARGET_MULTIPLE 100

void count_ways() {
    // counts[l] is the number of ways of splitting up k coins such that
    // the largest group size is l
    long *old_counts = calloc(MAX_COINS+1, sizeof(long));
    long *new_counts = calloc(MAX_COINS+1, sizeof(long));

    int group_size;

    int i;
    for(i = 0; i <= MAX_COINS; i++) {
        old_counts[i] = 1;
    }

    for(group_size = 2; group_size <= MAX_COINS; group_size++) {
        int group_count;
        for(group_count = 0; group_count <= (MAX_COINS / group_size); group_count++) {
            int n = group_count * group_size;
            int l;
            for(l = 0; l <= MAX_COINS-n; l++) {
                new_counts[l+n] += old_counts[l] % TARGET_MULTIPLE;
            }
        }

        printf("%ld ways with %d coins!\n", new_counts[group_size], group_size);
        if(new_counts[group_size] % TARGET_MULTIPLE == 0) {
            printf("BOOYAH!\n");
            exit(0);
        }
        fflush(stdout);

        memcpy(old_counts, new_counts, (MAX_COINS+1)*sizeof(long));
        memset(new_counts, 0, (MAX_COINS+1)*sizeof(long));
    }

    free(new_counts);
    free(old_counts);
    return;
}

int main(void) {
    int k;

    /*
    for(k = 1; k < MAX_COINS; k++) {
        long ways = count_ways(k);
        printf("%ld ways with %d coins!\n", ways, k);
        if(ways % TARGET_MULTIPLE == 0) {
            printf("booyah!\n");
            exit(0);
        }
    }*/
    count_ways();
            /*
    for(k = 1; k < MAX_COINS; k++) {
        long ways = count_ways(k);
    }*/

}
