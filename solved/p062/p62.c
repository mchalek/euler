#include <stdio.h>
#include <stdlib.h>

int cmp(const void *va, const void *vb) {
    long a = *((long *) va);
    long b = *((long *) vb);

    return (a-b) ? 2*(a>b)-1 : 0;
}

long count_digits(long x) {
    long ret = 0;
    long ndig = 0;

    while(x) {
        int digit = x % 10;
        x /= 10;

        ret += 1l << (6*digit);
        ndig ++;
    }

    return ret | ndig << 60;
}

int main(void) {
    int N = 10000;
    long *reps = malloc(N*sizeof(long));
    long i;

    for(i = 0; i < N; i++) {
        long cube = i*i*i;
        reps[i] = count_digits(cube);
    }

    qsort(reps, N, sizeof(long), cmp);

    long *candidates = malloc(N*sizeof(long));
    int ncand = 0;
    int k = 0;
    long current = 0;
    for(i = 0; i < N; i++) {
        if(reps[i] != current) {
            if(k == 5) {
                candidates[ncand++] = current;
            }
            current = reps[i];
            k = 1;
        } else {
            k++;
        }
    }

    for(i = 0; i < N; i++) {
        int j;
        long cube = count_digits(i*i*i);
        for(j = 0; j < ncand; j++) {
            if(candidates[j] == cube) {
                printf("%ld^3 == %ld (%lx)\n", i, i*i*i, cube);
                free(candidates);
                exit(0);
            }
        }
    }

    printf("No solution in specified cube window\n");

    free(candidates);

    return 0;
}
