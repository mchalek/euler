#include <stdio.h>
#include <prime.h>

//#define NMAX 150000000
#define NMAX 1000000l

int main()
{
    long *p, np;

    int seq[] = {7, 9, 13, 27};

    primes(NMAX + 100, &p, &np);

    long i;
    long sum = 0l;

    int nz = 0;
    for(i = 10; i < NMAX; i += 10) {
        if(!(i % 100000))
            printf("done with i == %ld\n", i);

        long i2 = i*i;
        if(isprime(i2+1, p, np) && isprime(i2+3, p, np)) {
            int j, k;
            bool hit = true;
            k = 0;
            for(j = 5; hit && j <= 27; j += 2) {
                if(seq[k] == j) {
                    hit &= isprime(i2+j, p, np);
                    k++;
                } else {
                    hit &= !isprime(i2+j, p, np);
                }
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
