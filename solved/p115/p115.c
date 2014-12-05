#include <stdio.h>
#include <string.h>

#define M 50

long doit(int m, int n)
{
    long n0[2][1 + n]; // first n end in black, next n in red
    long n1[2][1 + n];
    
    memset(n0, 0, sizeof(n0));
    memset(n1, 0, sizeof(n1));

    int i;
    n0[0][0] = 1; // 1 way to have nothing, say it ends in black so that there are no restrictions on red

    long result = 0l;

    for(i = 0; i < n; i++) {
        memset(n1, 0, sizeof(n1));
        int j;
        for(j = 0; j < n; j++) {
            // add a black rectangle to each one
            n1[0][j + 1] += n0[0][j] + n0[1][j];
        }

        for(j = 0; j < n; j++) {
            int k;
            for(k = m; j + k <= n; k++) {
                n1[1][j + k] += n0[0][j]; // can't do red after red, so only add to counts ending in black
            }
        }
        result += n1[0][n] + n1[1][n];

        memcpy(n0, n1, sizeof(n0));
    }

    return result;
}

int main(void)
{
    int n = M + 10;
    long result = doit(M, n);
    while(result <= 1000000) {
        printf("count[%d, %d]: %ld\n", M, n, result);
        result = doit(M, ++n);
    }

    printf("first exceeds 1M @ n == %d (count == %ld)\n", n, result);

}
