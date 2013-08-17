#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) ((a) < (b)) ? (a) : (b)

void get_pi(int N, int *pi)
{
    char *iscomp = calloc(N+1, sizeof(char));
    int i;
    iscomp[0] = 1;
    iscomp[1] = 1;

    pi[0] = 0;
    pi[1] = 0;
    for(i = 2; i <= N; i++) {
        if(!iscomp[i]) {
            int j;
            for(j = 2*i; j <= N; j += i)
                iscomp[j] = 1;
            pi[i] = 1+pi[i-1];
        } else
            pi[i] = pi[i-1];
    }

    free(iscomp);
}

int main(void)
{
    int N = 5000;
    int i;
    int *pi = malloc((1+N)*sizeof(int));
    get_pi(N, pi);

    for(i = 0; i < 1000; i++) {
        printf("pi[%d]: %d\n", i, pi[i]);
    }
    printf("pi[%d]: %d\n", N, pi[N]);
    int max_m = pi[N];
    long *bino = calloc((1+max_m),sizeof(long));
    long *tmp = malloc((1+max_m)*sizeof(long));

    if(!bino || !tmp) {
        fprintf(stderr, "allocation failure!!\n");
        exit(0);
    }

    bino[0] = 1;
    bino[1] = 1;

    for(i = 1; i <= 5; i++) {
        int j;

        fprintf(stderr, "memcpy\n");
        memcpy(tmp, bino, (1+max_m)*sizeof(long));
        for(j = 1; j < MIN(i+1, max_m); j++) {
            bino[j] += tmp[j-1];
        }
        bino[j] = 1;
        fprintf(stderr, "bino done\n");

        for(j = 0; j <= i; j++)
            printf("%4ld", bino[j]);

        printf("\n");
    }


    return 0;
}
