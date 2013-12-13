#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COINS 100000
#define TARGET_MULTIPLE 1000000

int main(void) {
    // counts[l] is the number of ways of splitting up k coins such that
    // the largest group size is l
    long *old_counts = calloc(MAX_COINS+1, sizeof(long));
    long *new_counts = calloc(MAX_COINS+1, sizeof(long));
    long *tmp;

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
                new_counts[l+n] += old_counts[l];
            }
        }

        int i;
        for(i = 0; i <= MAX_COINS; i++) {
            new_counts[i] %= TARGET_MULTIPLE;
        }

        printf("%ld ways with %d coins!\n", new_counts[group_size], group_size);
        if(!(new_counts[group_size] % TARGET_MULTIPLE)) {
            printf("BOOYAH!\n");
            exit(0);
        }
        fflush(stdout);
        
        tmp = old_counts;
        old_counts = new_counts;
        new_counts = tmp;

        memset(new_counts, 0, (MAX_COINS+1)*sizeof(long));
    }

    free(new_counts);
    free(old_counts);

    return 0;
}
