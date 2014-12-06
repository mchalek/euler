#include <prime.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define X 1000000000l
#define Y 1000l
#define Z 1000000000000000l
//#define Z 1000l

#define NEXT(a) (6*(a)*(a) + 10*(a) + 3) // == (3a + 3)(2a + 1) + a

long B(long p, char *work) {
    memset(work, 0, p*sizeof(char));

    long a = 1;
    long i = 0;

    while(!work[a]) {
        i++;
        work[a] = true;
        a = NEXT(a) % p;
    }

    long cycle_len = i;
    long cycle_start = a;

    long z = Z;
    a = 1;
    while(a != cycle_start) {
        cycle_len--;
        z--;
        a = NEXT(a) % p;
    }

    printf("cycle len for p == %ld is %ld (repeats at %ld)\n", p, cycle_len, cycle_start);

    z %= cycle_len;

    a = cycle_start;
    for(i = 0; i < z - 1; i++) {
        a = NEXT(a) % p;
    }

    printf("a_%ld for p == %ld is %ld\n", Z, p, a);
    return a;
}

int main()
{
    long *p, np;
    primes(100000, &p, &np);

    long n_target = 0;
    long *tp = malloc((Y+1)*sizeof(long));

    long i;
    char *work = calloc(X+Y, sizeof(char));
    long result = 0;
    for(i = X; i <= X+Y; i++) {
        if(isprime(i, p, np)) {
            printf("%ld is prime\n", i);
            result += B(i, work);
            tp[n_target++] = i;
        } else {
            //printf("%ld is not prime\n", i);
        }
    }
    printf("%ld target primes\n", n_target);
    printf("B(%ld, %ld, %ld) == %ld\n", X, Y, Z, result);

    free(p);

    return 0;

}
