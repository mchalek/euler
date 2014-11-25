#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int factorial(int N, int k) {
    if(N == k)
        return 1;

    return N*factorial(N-1, k);
}

int nchoosek(int N, int k) {
    return factorial(N, k) / factorial(N-k, 0);
}

int _popcnt(uint64_t item) {
    int ret = 0;
    while(item) {
        ret += (item & 1ul);
        item >>= 1;
    }

    return ret;
}

int item_sum(int items[], int mask) {
    int ret = 0;
    int index = 0;

    while(mask) {
        if(mask & 1) {
            ret += items[index];
        }

        index++;
        mask >>= 1;
    }

    return ret;
}

int icmp(const void *va, const void *vb) {
    int a = *((int *) va);
    int b = *((int *) vb);

    return a-b;
}

int special_sum(int N, int items[]) {
    int **ksums = malloc((1 + N) * sizeof(int *));
    int *kcount = calloc((1 + N), sizeof(int));

    int i;

    for(i = 0; i <= N; i++)
        ksums[i] = malloc(nchoosek(N, i) * sizeof(int));

    for(i = 1; i < (1 << N); i++) {
        int count = _popcnt(i);
        int index = kcount[count]++;

        int sum = item_sum(items, i);

        ksums[count][index] = sum;
    }

    for(i = 1; i < N; i++)
        qsort(ksums[i], kcount[i], sizeof(int), icmp);

    bool is_special = true;
    for(i = 1; i < N && is_special; i++) {
        // check duplicate sums
        int j;
        for(j = 1; j < kcount[i]; j++) {
            if(ksums[i][j] == ksums[i][j-1]) {
                is_special = false;
                break;
            }
        }

        // check order
        if(ksums[i][kcount[i]-1] >= ksums[i+1][0])
            is_special = false;
    }

    int ret = 0;
    if(is_special) {
        for(i = 0; i < N; i++)
            ret += items[i];
    }

    for(i = 0; i < N; i++)
        free(ksums[i]);
    free(ksums);
    free(kcount);

    return ret;
}

void iterate(int *min_sum, int depth, int max_depth, int items[])
{
    int i;

    if(depth == max_depth) {
        int cur_sum = 0;
        for(i = 0; i < depth; i++) {
            cur_sum += items[i];
        }
        int r0 = special_sum(max_depth, items);

        if(r0) {
            if(!*min_sum || (*min_sum > 0 && cur_sum < *min_sum)) {
                *min_sum = cur_sum;
                printf("new min: ");
                for(i = 0; i < max_depth; i++)
                    printf("%d", items[i]);
                printf("\n");
            }
        }

        return;
    }

    int min, max;

    if(depth > 1) {
        min = items[depth-1]+1;
        max = items[0] + items[1];
    } else if(depth == 1) {
        min = items[0] + 1;
        max = 40;
    } else {
        min = 17;
        max = 30;
    }

    for(i = min; i < max; i++) {
        if(!depth)
            printf("checking all items beginning with element %d\n", i);
        items[depth] = i;
        iterate(min_sum, 1+depth, max_depth, items);
    }
}

int main(void) {
    int min_sum = 0;
    int items[7];
    iterate(&min_sum, 0, 7, items);

    return 0;
}
