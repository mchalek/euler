#include <stdio.h>

#define MAX_N 100000000000000000l
//#define MAX_N 1000000l

int main(void)
{
    long int f, f1, f2, f0, cn, cm, c0, sum;
    long int flist[100], clist[100], delta;
    int n, k;

    flist[0] = 1;
    flist[1] = 1;
    clist[0] = 1;
    clist[1] = 2;
    n = 2;

    f1 = 1;
    f2 = 1;
    cn = 2;
    cm = 1;
    do {
        c0 = cn;
        cn += cm + f1 - 1;
        cm = c0;

        clist[n] = cn;
        
        f0 = f2;
        f2 = f1;
        f1 += f0;

        flist[n] = f1 + f2;

        n++;

//        printf("c[%lld] == %lld\n", f1 + f2, cn);
    } while(f1 + f2 < MAX_N);

    n--;
    while(flist[n] > MAX_N)
        n--;

    sum = clist[n];
    delta = MAX_N - flist[n];

    k = 1;
    while(delta) {
        if(delta >= flist[n]) {
            delta -= flist[n];
            sum += k * flist[n] + clist[n];
            k++;
        }
        n--;
    }

    printf("sum to MAX_N == %lld\n", sum - k);

}
