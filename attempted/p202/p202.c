#include<stdio.h>

long gcd(long a, long b) {
    if(a > b) {
        return gcd(b, a);
    }

    long mod = b % a;
    if(!mod) {
        return a;
    }

    return gcd(a, mod);
}

long solve(long r) {
    long d = (r + 3) / 2;
    printf("depth: %ld\n", d);

    long start = -d + ((3 + ((-d) % 3)) % 3);

    printf("start: %ld\n", start);

    long nsol = 0;
    long i;
    long count_since_print = 0;
    long done = 0;
    for(i = start; i < start / 2; i += 3) {
        if(gcd(d, -i) == 1) {
            //printf("solution at %ld / %ld\n", d, i);
            nsol += 2;
        }
        done += 1;
        count_since_print += 1;
        if(count_since_print > 1000000) {
            printf("%ld items remaining\n", (start/2 - i) / 3);
            count_since_print = 0;

        }
    }
    printf("number of solutions for r == %ld: %ld\n", r, nsol);
    return nsol;
}

int main() {
    solve(7);
    solve(9);
    solve(11);
    solve(13);
    solve(1000001);
    //solve(12017639147);
}
