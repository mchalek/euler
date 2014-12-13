#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int main()
{
    int *S = malloc(100*sizeof(int));
    int i;
    for(i = 0; i < 100; i++) {
        S[i] = (i+1)*(i+1);
    }

    int max = 0;
    for(i = 0; i < 50; i++) {
        max += S[99-i];
    }
    printf("max is: %d\n", max);

    long **sums = malloc(51*sizeof(long *));
    long **tmp = malloc(51*sizeof(long *));
    for(i = 0; i < 51; i++) {
        sums[i] = calloc(max+1, sizeof(long));
        tmp[i] = calloc(max+1, sizeof(long));
    }

    sums[0][0] = 1;
    
    for(i = 0; i < 100; i++) {
        int j;
        for(j = 0; j < MIN(i + 1, 51); j++) {
            memcpy(tmp[j], sums[j], (max+1)*sizeof(long));
        }

        int item = S[i];
        for(j = 0; j < MIN(i + 1, 50); j++) {
            int k;
            for(k = 0; k + item <= max; k++) {
                sums[j+1][k + item] += tmp[j][k];
            }
        }
    }

    long sum = 0;
    for(i = 0; i <= max; i++) {
        if(sums[50][i] == 1)
            sum += i;
    }

    printf("result: %ld\n", sum);
    
    return 0;
}
