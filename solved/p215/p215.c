#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// relatively simple: collect set of valid rows, then compute valid 
// transitions between rows. Finally, assemble counts via dynamic programming

#define WIDTH 32
#define HEIGHT 10

long get_valid_rows(int current, uint64_t row, long *nrows, uint64_t rows[]) {
    if(current > WIDTH)
        return 0;

    if(current == WIDTH) {
        if(rows) {
            rows[*nrows] = row ^ (1l << WIDTH);
            (*nrows)++;
        }
        return 1;
    }

    return get_valid_rows(2+current, row | (1l << (2+current)), nrows, rows) +
        get_valid_rows(3+current, row | (1l << (3+current)), nrows, rows);
}

int main(void) 
{
    long num_valid_rows = get_valid_rows(0, 0, NULL, NULL);
    uint64_t *valid_rows = malloc(num_valid_rows*sizeof(uint64_t));
    num_valid_rows = 0;
    get_valid_rows(0, 0, &num_valid_rows, valid_rows);

    printf("%ld attainable structures\n", num_valid_rows);

    int **transitions = malloc(num_valid_rows * sizeof(int *));
    int *nalloc = malloc(num_valid_rows * sizeof(int));
    int *ntrs = calloc(num_valid_rows, sizeof(int));
    int i;
    for(i = 0; i < num_valid_rows; i++) {
        nalloc[i] = 128;
        transitions[i] = calloc(nalloc[i], sizeof(int));
    }

    // build list of valid transitions
    for(i = 0; i < num_valid_rows; i++) {
        int j;
        for(j = i + 1; j < num_valid_rows; j++) {
            if(valid_rows[i] & valid_rows[j])
                continue;

            if(nalloc[i] == ntrs[i]) {
                nalloc[i] <<= 1;
                transitions[i] = realloc(transitions[i], nalloc[i]*sizeof(int));
            }

            transitions[i][ntrs[i]] = j;
            ntrs[i]++;

            if(nalloc[j] == ntrs[j]) {
                nalloc[j] <<= 1;
                transitions[j] = realloc(transitions[j], nalloc[j]*sizeof(int));
            }

            transitions[j][ntrs[j]] = i;
            ntrs[j]++;
        }
    }

    for(i = 0; i < num_valid_rows; i++) {
        transitions[i] = realloc(transitions[i], ntrs[i]*sizeof(int));
    }
    free(nalloc);

    // now we build by DP
    long *prev = malloc(num_valid_rows * sizeof(long));
    for(i = 0; i < num_valid_rows; i++) {
        prev[i] = 1;
    }

    int cur_height;
    for(cur_height = 1; cur_height < HEIGHT; cur_height++) {
        long *cur = calloc(num_valid_rows, sizeof(long));
        for(i = 0; i < num_valid_rows; i++) {
            int j;
            for(j = 0; j < ntrs[i]; j++) {
                cur[transitions[i][j]] += prev[i];
            }
        }

        long *tmp = prev;
        prev = cur;
        free(tmp);
    }

    long result = 0;
    for(i = 0; i < num_valid_rows; i++)
        result += prev[i];

    printf("W(%d, %d) == %ld\n", WIDTH, HEIGHT, result);
    return 0;
}
