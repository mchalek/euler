#include <prime.h>

int main(void)
{
    long *p, np;

    primes(20, &p, &np);

    int i;
    for(i = 0; i < np; i++) {
        printf("%d is prime\n", p[i]);
    }
}
