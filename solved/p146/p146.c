#include <stdio.h>
#include <prime.h>

#define NMAX 150000000l
//#define NMAX 1000000l

long *p, np;
int seq[] = {7, 9, 13, 27};

bool check(long n) {
    long n2 = n*n;
    bool hit = false;
    if(isprime(n2+1, p, np) && isprime(n2+3, p, np)) {
        int j, k;
        hit = true;
        k = 0;
        for(j = 5; hit && j <= 27; j += 2) {
            if(seq[k] == j) {
                hit &= isprime(n2+j, p, np);
                k++;
            } else {
                hit &= !isprime(n2+j, p, np);
            }
        }
    }

    return hit;
}

int main()
{
    primes(NMAX + 100, &p, &np);

    long i;
    long sum = 0l;

    int nz = 0;
    for(i = 10; i < NMAX; i += 10) {
        if(!(i % 100000))
            printf("done with i == %ld\n", i);

        if(!(i % 3))
            continue;

        // only valid values for i % 7 are {3, 4}
        long mod7 = i % 7;
        if(!(mod7 == 3 || mod7 == 4))
            continue;

        long mod11 = i % 11;
        if(mod11 == 2 || mod11 == 3 || mod11 == 8 || mod11 == 9)
            continue;

        // invalid values for i % 13 are {0, 5, 6, 7, 8}
        long mod13 = i % 13;
        if((mod13 == 0) || (mod13 > 4 && mod13 < 9)) 
            continue;

        bool hit = check(i);

        if(hit) {
            printf("hit for i == %ld\n", i);
            sum += i;
            nz++;
        }
    }

    printf("final i: %ld\n", i);
    printf("sum of target numbers: %ld\n", sum);
    printf("%d primes of this form below %ld\n", nz, NMAX);

    return 0;
}
