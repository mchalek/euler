#include <stdio.h>
#include <prime.h>

#define MAX_P 10000000
#define TARGET_REM 10000000000l

// (p-1)^n + (p+1)^n ==
//      2 : n is even
//    2np : n is odd
// so loop over odd n, checking for 2np > TARGET_REM

int main()
{
    long *p, np;
    primes(MAX_P, &p, &np);

    long n;
    for(n = 1; n < np; n += 2) {
        long pn = p[n-1];
        long p2 = pn*pn;
        long rem = 2*n*pn % p2;

        if(rem > TARGET_REM) {
            printf("remainder first exceeds %ld for p_%ld == %ld\n", TARGET_REM, n, pn);
            break;
        }
    }

    return 0;
}
