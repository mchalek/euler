#include <stdio.h>
#include <string.h>

// assemble all valid count vectors, for each possible distinct color count,
// using binomial coefficients to account for the number of ways in which
// each count vector can exist

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

long nCr(int n, int r)
{
    long ret = 1;
    int i;
    for(i = n-r+1; i <= n; i++) {
        ret *= i;
    }

    for(i = 1; i <= r; i++)
        ret /= i;

    return ret;
}

long build(int ncol, int depth, int rem, long weight) 
{
    if(depth == ncol)
        return weight;

    int min = MAX(1, rem - 10*(ncol-depth-1));
    int max = MIN(rem, 10);

    int count;
    long ret = 0;
    for(count = min; count <= max; count++) {
        ret += build(ncol, depth+1, rem - count, weight * nCr(10, count));
    }

    return ret;
}

int main()
{
    long S = 0;
    long S0 = 0;
    int n;

    for(n = 2; n <= 7; n++) { // cannot have fewer than 2
        long Sn = build(n, 0, 20, 1);
        long ncr = nCr(7, n);
        S0 += Sn * ncr;
        S += n*Sn * ncr;
        printf("ways for n == %d: %ld\n", n, Sn);
    }
    printf("total sum: %ld\n", S);
    printf("expected: %ld / %ld == %.9f\n", S, S0, ((double) S) / S0);
    return 0;
}
