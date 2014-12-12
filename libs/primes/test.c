#include <prime.h>
#include <stdio.h>

int main(void)
{
    long *p, np;

    primes(20, &p, &np);

    int i;
    for(i = 0; i < np; i++) {
        printf("%ld is prime\n", p[i]);
    }

    return 0;
}
