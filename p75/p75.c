#include <stdio.h>
#include <math.h>

#define N 1500000

int find_pairsum(long pairsum, long *squares, long L, long *s1, long *s2)
{
    long i;
    for(i = 1; squares[i] < (pairsum/2+1); i++) {
        long target = pairsum - i*i;
        long *hit = bsearch(&target, squares + (N/2-1), (N/2+1), sizeof(long));

    }
}

int main(void)
{
    long i;

    long *squares = malloc((1+N)*sizeof(long));
    int *counts = calloc((1+N), sizeof(int));

    for(i = 0; i <= N; i++)
        squares[i] = i*i;

    long L;

    for(L = 1; L < (N+1); L++) {
        long j;
        long L2 = L*L;
        for(j = 1; j < (L/2+1); j++) {
            long pairsum = L2 - j*j; 
            long c = count_pairsum(pairsum, squares, L, &s1, &s2);
        }
    }
}
