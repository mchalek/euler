#include <miller_rabin.h>
#include <stdio.h>

#define MAX_N 10000l

int main(void)
{
    long n;

    long count = 0;
    for(n = 2; n <= MAX_N; n++) {
        long t = 2*n*n - 1;

        count += mr_isprime(t);
    }

    printf("%ld numbers t(n) are prime for n <= %ld\n", count, MAX_N);

    return 0;
}
