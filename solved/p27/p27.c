#include <stdio.h>
#include <string.h>

int PMAX = 10000000;
int coefmax = 10000;

int count_prime_seq(int b, int a, int iscomp[])
{
    int n = 2; // we already restrict so n < 2 yields 2 primes
    
    while(!iscomp[((n*n + a*n + b) > 0) ? (n*n + a*n + b) : -(n*n + a*n + b)])
        n++;

    return n;
}

int main(void)
{
    int iscomp[PMAX + 1];
    int primes[PMAX];
    int np = 0;
    int a, b;
    int amax, bmax, nmax;
    int n, i, j;
    
    memset(iscomp, 0, sizeof(iscomp));
    iscomp[0] = 1;
    iscomp[1] = 1;

    for(i = 2; i < PMAX; i++) {
        if(!iscomp[i]) {
            primes[np++] = i;
            j = 2*i; 
            while(j < PMAX) {
                iscomp[j] = 1;
                j += i;
            }
        }
    }

    b = 0;
    int x;
    nmax = 0;
    while(primes[b] < coefmax) {
        for(a = 0; a < coefmax; a++) {
            x = 1 + primes[b] + a;
            if(!iscomp[x]) {
                n = count_prime_seq(primes[b], a, iscomp);
                if(n > nmax) {
                    nmax = n;
                    bmax = primes[b];
                    amax = a;
                }
            }

            x = 1 + primes[b] - a;
            x = (x < 0) ? -x : x;
            if(!iscomp[x]) {
                n = count_prime_seq(primes[b], -a, iscomp);
                if(n > nmax) {
                    nmax = n;
                    bmax = primes[b];
                    amax = -a;
                }
            }
            x = 1 - primes[b] + a;
            x = (x < 0) ? -x : x;
            if(!iscomp[x]) {
                n = count_prime_seq(-primes[b], a, iscomp);
                if(n > nmax) {
                    nmax = n;
                    bmax = -primes[b];
                    amax = a;
                }
            }
            x = 1 - primes[b] - a;
            x = (x < 0) ? -x : x;
            if(!iscomp[x]) {
                n = count_prime_seq(-primes[b], -a, iscomp);
                if(n > nmax) {
                    nmax = n;
                    bmax = -primes[b];
                    amax = -a;
                }
            }
        }
        b++;
    }

    printf("Sequence of %d primes generated by: n^2 + (%d) n + (%d)\n", nmax, amax, bmax);
    printf("a*b == %d\n", amax*bmax);

    return 0;
}
