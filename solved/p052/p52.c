#include <stdio.h>
#include <math.h>
#include <string.h>

void decompose(int a, int counts[])
{
    memset(counts, 0, 10*sizeof(int));
    while(a) {
        counts[a % 10]++;
        a /= 10;
    }
}

int cmp(int counts1[], int counts2[])
{
    int i;
    for(i = 0; i < 10; i++)
        if(counts1[i] != counts2[i])
            return 1;

    return 0;
}

int check(int x)
{
    int counts1[10], counts2[10];
    decompose(2*x, counts1);
    decompose(3*x, counts2);
    if(cmp(counts1, counts2))
        return 0;
    decompose(4*x, counts2);
    if(cmp(counts1, counts2))
        return 0;
    decompose(5*x, counts2);
    if(cmp(counts1, counts2))
        return 0;
    decompose(6*x, counts2);
    if(cmp(counts1, counts2))
        return 0;

    return 1;
}

int main(void)
{
    int x = 0;
    int stop = 0;
    while(!stop) {
        x++;
        while(log10(2*x) - log10(6*x) >= 1.0)
            x++;
        if((x % 10000 == 0) && x)
            printf("checking x == %d\n", x);
        stop = check(x);
    }
    printf("x == %d\n", x);
    int i;
    for(i = 2; i <= 6; i++) {
        printf("%d*x == %d\n", i, i*x);
    }
    return 0;
}
