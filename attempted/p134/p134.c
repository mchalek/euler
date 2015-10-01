#include <stdio.h>
#include <prime.h>

// can't just exhaust, need to build constructively

int main()
{
    long *p, np;

    primes(1000000, &p, &np);

    long S = 0;

    int i;
    long modulus = 10;
    // start i at 2 => p[i] == 5
    for(i = 2; i < np - 1; i++) {
        if(!(i % 1000))
            printf("done with p[%d] == %ld\n", i-1, p[i-1]);
        long pn = p[i];
        long pn1 = p[i+1];
        if(pn > modulus)
            modulus *= 10;

        long z = pn1;
        while(z % modulus != pn) {
            z += pn1;
        }

        S += z;
        printf("solution for (%ld, %ld): %ld\n", pn, pn1, z);
    }

    return 0;
}
