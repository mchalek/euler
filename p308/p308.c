#include <stdio.h>
#include <stdlib.h>

int n[] = {17, 78, 19, 23, 29, 77, 95, 77, 1, 11, 13, 15, 1, 55};
int d[] = {91, 85, 51, 38, 33, 29, 23, 19, 17, 13, 11, 2, 7, 1};
int k = 14;

int is_pow_2(unsigned long k)
{
    while(!(k & 1))
        k >>= 1;

    return !(k & (~1));
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Need input argument.\n");
        exit(0);
    }
    unsigned int KSTART = atoi(argv[1]);
    unsigned long k0 = KSTART;
    int i;
    int steps = 0;
    do {
        i = 0;
        while(k0 % d[i])
            i++;
        
        k0 = k0 / d[i] * n[i];
        steps++;

        printf("times fraction %d; k0: %ld\n", i, k0);
    } while(!is_pow_2(k0));
    printf("%d steps between %ld and %ld.\n", steps, KSTART, k0);
    return 0;
}
