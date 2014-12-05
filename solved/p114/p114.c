#include <stdio.h>
#include <string.h>

#define N 50

int main()
{
    long n0[2][1 + N]; // first N end in black, next N in red
    long n1[2][1 + N];
    
    memset(n0, 0, sizeof(n0));
    memset(n1, 0, sizeof(n1));

    int i;
    n0[0][0] = 1; // 1 way to have nothing, say it ends in black so that there are no restrictions on red

    long result = 0l;

    for(i = 0; i < N; i++) {
        memset(n1, 0, sizeof(n1));
        int j;
        for(j = 0; j < N; j++) {
            // add a black rectangle to each one
            n1[0][j + 1] += n0[0][j] + n0[1][j];
            //printf("n1[0][%d] == %ld\n", j+1, n1[0][j + 1]);
        }

        for(j = 0; j < N; j++) {
            int k;
            for(k = 3; j + k <= N; k++) {
                n1[1][j + k] += n0[0][j]; // can't do red after red, so only add to counts ending in black
                /*
                if(n0[0][j])
                    printf("n0[0][%d] == %ld => n1[1][%d] == %ld\n", j, n0[0][j], j+k, n1[1][j + k]);
                    */
            }
        }
        result += n1[0][N] + n1[1][N];

        printf("====== iteration %d complete, total @%ld ========\n", i+1, result);

        memcpy(n0, n1, sizeof(n0));
    }

    printf("solution: %ld\n", result);

}
