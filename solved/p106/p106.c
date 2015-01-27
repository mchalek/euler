#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int factorial(int N, int k) {
    if(N == k)
        return 1;

    return N*factorial(N-1, k);
}

int nchoosek(int N, int k) {
    return factorial(N, k) / factorial(N-k, 0);
}

int _popcnt(uint64_t item) {
    int ret = 0;
    while(item) {
        ret += (item & 1ul);
        item >>= 1;
    }

    return ret;
}

int num_pairs(int N) {
    // first make sure we can account for their tallies of the number of sets
    int size0, size1;
    int count = 0;
    for(size0 = 1; size0 < N; size0++) {
        for(size1 = 1; size0 + size1 <= N; size1++) {
            count += nchoosek(N, size0) * nchoosek(N-size0, size1);
        }
    }

    return count / 2; // symmetric
}

int check_guaranteed_inequality(int a, int b) {
    // require a < b
    if(a > b)
        return check_guaranteed_inequality(b, a);

    int ca = 0;
    int cb = 0;

    // checks that each element of a has a corresponding element in b that is larger than it
    while(a) {
        while(!(a & 1)) {
            a >>= 1;
            ca++;
        }
        a >>= 1;

        while(!(b & 1)) {
            b >>= 1;
            cb++;
        }
        b >>= 1;

        if(ca > cb)
            return 0;
    }

    return 1;
}

int count_required_checks(int N) {
    int count = 0;
    int max_size = N/2;

    int max = 1 << N;

    int u0, u1;
    for(u0 = 1; u0 < max; u0++) {
        int pc0 = _popcnt(u0);
        if(pc0 < 2 || pc0 > max_size)
            continue;

        for(u1 = 1; u1 < u0; u1++) {
            if(u0 & u1)
                continue;
            int pc1 = _popcnt(u1);
            if(pc1 != pc0) // no need to check different sized sets
                continue;

            if(check_guaranteed_inequality(u1, u0)) 
                continue;
            
            count++;
        }

    }

    return count;
}

int num_comp(int N) {

    return 0;
}

int main(void) {
    printf("num_pairs[4] == %d\n", num_pairs(4));
    printf("num_pairs[7] == %d\n", num_pairs(7));
    printf("num_pairs[12] == %d\n", num_pairs(12));

    printf("checks_required[4] == %d\n", count_required_checks(4));
    printf("checks_required[7] == %d\n", count_required_checks(7));
    printf("checks_required[12] == %d\n", count_required_checks(12));

    return 0;
}
