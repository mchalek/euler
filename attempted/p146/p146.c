#include <stdio.h>
#include <prime.h>

//#define NMAX 150000000
#define NMAX 1000000l

int main()
{
    long *p, np;

    int seq[] = {3, 7, 9, 13, 27};
    int nseq = sizeof(seq)/sizeof(int);

    primes(NMAX + 100, &p, &np);

    long i;
    long sum = 0l;

    int nz = 0;
    for(i = 10; i < NMAX; i += 10) {
        if(!(i % 100000))
            printf("done with i == %ld\n", i);

        long i2 = i*i;
        if(isprime(i2+1, p, np)) {
            //printf("further testing for i == %ld (%ld)\n", i, i*i+1);
            int j;
            bool hit = true;
            for(j = 0; hit && j < nseq; j++) {
                if(j) {
                    int k;
                    for(k = seq[j-1] + 2; k < seq[j]; k += 2) {
                        hit &= !isprime(i2+k, p, np);
                    }
                }
                bool test = isprime(i2+seq[j], p, np);
                hit &= test;
            }
            
            if(hit) {
                printf("hit for i == %ld\n", i);
                sum += i;
                nz++;
            }
        }
    }

    printf("final i: %ld\n", i);
    printf("sum of target numbers: %ld\n", sum);
    printf("%d primes of this form below %ld\n", nz, NMAX);

    return 0;
}
