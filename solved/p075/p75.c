#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1500000

long largest_subsquare(long d, long *squares)
{
    long i = 1;
    long ret = 0;

    while(squares[i] <= d) {
        if(!(d % squares[i]))
            ret = i;

        i++;
    }

    return ret;

}

int main(void)
{
    long i;

    long *squares = malloc((1+N)*sizeof(long));
    int *counts = calloc((1+N), sizeof(int));

    for(i = 0; i <= N; i++)
        squares[i] = i*i;

    long a, b, c, d;

    for(d = 1; d <= (N+1)/2; d++) {
        long x = largest_subsquare(d, squares);
        long residual = d / (x*x);
        //printf("residual(%ld) == %ld\n", d, residual);

        long ind = 1;
        long e = residual*squares[ind];
        b = ind*x*residual;

        a = (e - d) / 2;

        c = d + a;
        //printf("-trying %d/%d/%d (e: %d; d: %d)\n", a, b, c, e, d);
        long L = a+b+c;
        while(L <= N) {
            if(!((e - d) % 2) && a > 0 && b > 0 && a < b) {
                //printf("%ld^2 + %ld^2 == %ld^2\n", a, b, c);
                counts[L]++;
            }
            ind++;
            e = residual*squares[ind];
            b = ind*x*residual;

            a = (e - d) / 2;
            c = d + a;
        //printf("+trying %d/%d/%d (e: %d; d: %d)\n", a, b, c, e, d);
            L = a+b+c;
        }
    }

    int result = 0;
    for(d = 1; d <= N; d++)
        result += counts[d] == 1;
        

    //int checks[] = {12,24,30,36,40,48,120};
    //int ncheck = sizeof(checks)/sizeof(int);
    //for(d = 0; d < ncheck; d++)
        //printf("counts[%d]: %d\n", checks[d], counts[checks[d]]);
    printf("result: %d\n", result);
    return 0;
}
