#include <stdio.h>
#include <prime.h>
#include <stdlib.h>

long ndig(long p) {
    long n = 0;
    while(p) {
        n++;
        p /= 10;
    }

    return n;
}

long compute_z(long r, long p2) {
    if(!r) {
        return 1l;
    }

    return (10 * compute_z(r - 1, p2)) % p2;
}

long tenexp(long r) {
    if(!r) {
        return 1;
    }

    return 10*tenexp(r-1);
}

long build_result(long r, long p1, long x) {
    return tenexp(r)*x + p1;
}

long compute_S(long p1, long p2) {
    long r = ndig(p1);

    long z = compute_z(r, p2);

    long q = z;
    long count = 1;
    while(q != (p2 - p1)) {
        count++;

        q += z;
        q %= p2;
    }

    return build_result(r, p1, count);
}

int main(void) {
    long np, *p;

    primes(1000010, &p, &np);

    long ip1;
    long result = 0l;

    for(ip1 = 2; p[ip1] <= 1000000; ip1++) {
        long p1 = p[ip1];
        long p2 = p[1 + ip1];

        long S = compute_S(p1, p2);
        result += S;

        if(!(ip1 % 1000)) {
            printf("%ld / %ld: %ld\n", p1, p2, S);
        }
    }

    printf("result: %ld\n", result);

    return 0;
}
