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

int item_sum(int N, int items[], int mask) {
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

        int sum = item_sum(N, items, i);

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

int read_item(int *start, int stop, char buf[]) {
    int ret = atoi(buf + *start);
    while(isdigit(buf[*start])) {
        (*start)++;
        if(*start == stop)
            return ret;
    }

    while(!isdigit(buf[*start])) {
        (*start)++;
        if(*start == stop)
            return ret;
    }

    return ret;
}

void read_items(char buf[], int *nitems, int items[]) {
    int start = 0;
    int stop = strlen(buf);
    *nitems = 0;

    do {
        int item = read_item(&start, stop, buf);
        items[*nitems] = item;
        (*nitems)++;
    } while(start < stop);
}

int main(void) {
    int test0[] = {81, 88, 75, 42, 87, 84, 86, 65};
    int test1[] = {157, 150, 164, 119, 79, 159, 161, 139, 158};

    int r0 = special_sum(8, test0);
    int r1 = special_sum(9, test1);

    if(r0 == -1) {
        printf("test0 is not special\n");
    } else {
        printf("test0 is special, with S(_) == %d\n", r0);
    }

    if(r1 == -1) {
        printf("test1 is not special\n");
    } else {
        printf("test1 is special, with S(_) == %d\n", r1);
    }

    FILE *fp = fopen("sets.txt", "r");
    char buf[1024];
    
    int sum = 0;
    int special_count = 0;
    int count = 0;
    while(NULL != fgets(buf, sizeof(buf), fp)) {
        count++;
        int *items = malloc(12*sizeof(int));
        int nitems = 0;

        read_items(buf, &nitems, items);

        printf("read set: {%d", items[0]);
        int z;
        for(z = 1; z < nitems; z++) {
            printf(", %d", items[z]);
        }
        printf("}");

        int result = special_sum(nitems, items);

        if(result) {
            printf(" (special, sum is %d)\n", result);
            special_count++;
            sum += result;
        } else {
            printf(" (not special)\n");
        }
    }

    printf("%d / %d are special\n", special_count, count);
    printf("sum of special sets: %d\n", sum);
}
