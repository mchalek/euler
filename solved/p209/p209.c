#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* Some observations:
 * There are 64 possible inputs (a, b, c, d, e, f).
 * - The transformation specified, t(a,b,c,d,e,f) => t(b,c,d,e,f,a ^ (b & c)),
 *   defines a permutation of the inputs (i.e. it is 1-1)
 * - This permutation has a few cycles in it.  We can study the cycles
 *   independently, but one of them is especially big (46 items long)
 *   This is 23 pairs, each with 3 possible values, but certain values in
 *   some pairs rule out values in others...
 * - Is this equivalent to counting bit strings where no 2 adjacent entries are 1?
 */

int transform(int x) {
    int a = 1 & (x >> 5);
    int b = 1 & (x >> 4);
    int c = 1 & (x >> 3);

    return ((x & 0x1f) << 1) | (a ^ (b & c));
}

long cycle_count(int length) {
    // All we need is the length of the cycle, we want to count bit strings
    // where no 2 adjacent entries are 1
    
    long count00 = 1; // # of sequences starting at 0, with terminal entry 0
    long count01 = 0; // # of sequences starting at 0, with terminal entry 1
    long count10 = 0; // # of sequences starting at 1, with terminal entry 0
    long count11 = 1; // # of sequences starting at 1, with terminal entry 1

    int i;
    for(i = 1; i < length; i++) {
        long tmp00 = count01 + count00;
        long tmp01 = count00;
        long tmp10 = count11 + count10;
        long tmp11 = count10;

        count00 = tmp00;
        count01 = tmp01;
        count10 = tmp10;
        count11 = tmp11;
    }

    // must discard count11 because it's invalid
    return count00 + count01 + count10;
}

int main(void) {
    int map[64];
    int i;

    for(i = 0; i < 64; i++) {
        map[i] = transform(i);
    }

    long result = 1;
    int n_cycles = 0;
    unsigned char cycle_ind[64];
    memset(cycle_ind, 0xff, sizeof(cycle_ind));
    for(i = 0; i < 64; i++) {
        if(cycle_ind[i] != 0xff)
            continue;

        int cycle_length = 1;
        cycle_ind[i] = (unsigned char) n_cycles;
        int j = map[i];
        printf("cycle %d: %2d => %2d", n_cycles, i, j);
        while(j != i) {
            cycle_length++;
            cycle_ind[j] = (unsigned char) n_cycles;
            j = map[j];
            printf(" => %2d", j);
        }

        long nseq = cycle_count(cycle_length);
        printf(" (length is %d, %ld valid sequences)\n", cycle_length, nseq);

        result *= nseq;

        n_cycles++;
    }

    printf("result: %ld\n", result);
    return 0;
}
