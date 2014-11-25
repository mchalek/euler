#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

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

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("SYNTAX: %s N\n", argv[0]);
        exit(0);
    }
    int N = strtol(argv[1], NULL, 10);
    int i, j;
    int *pi = malloc((1+N)*sizeof(int));
    get_pi(N, pi);

    /*
    for(i = 0; i < 1000; i++) {
        printf("pi[%d]: %d\n", i, pi[i]);
    }*/
    printf("pi[%d]: %d\n", N, pi[N]);
    int max_m = pi[N];
    long *bino = calloc((2+max_m),sizeof(long));

    if(!bino) {
        fprintf(stderr, "allocation failure!!\n");
        exit(0);
    }

    bino[0] = 1;
    bino[1] = 1;

    for(i = 1; i <= N; i++) {
        if(i % 100000 == 0)
            printf("i == %d\n", i);
        int cur_table_size = MIN(1+i, max_m);

        long last, tmp;
        last = bino[0];
        for(j = 1; j < cur_table_size; j++) {
            tmp = bino[j];
            bino[j] += last;
            bino[j] %= 1000000007;
            last = tmp;
        }
        bino[cur_table_size] = 1;
    }


    return 0;
}
