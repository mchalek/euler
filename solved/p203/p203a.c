#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "SYNTAX: %s NUM_ROWS\n", argv[0]);
        exit(0);
    }
    int N = atoi(argv[1]);
    long triangle[52][52];
    triangle[0][0] = 1l;
    triangle[1][0] = 1l;
    triangle[1][1] = 1l;
    int i;
    printf("1\n");
    for(i = 2; i < N; i++) {
        int k;
        for(k = 1; k < i; k++) {
            triangle[i][k] = triangle[i-1][k-1] + triangle[i-1][k];
            printf("%ld\n", triangle[i][k]);
        }
        triangle[i][0] = 1l;
        triangle[i][i] = 1l;
    }

    return 0;
}
