#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* Some observations:
 * There are 64 possible inputs (a, b, c, d, e, f).
 * - The transformation specified, t(a,b,c,d,e,f) => t(b,c,d,e,f,a ^ (b & c)),
 *   defines a permutation of the inputs (i.e. it is 1-1)
 * - Let I be an input, and pI be the permuted input.  The problem constraint
 *   t(I) & t(pI) == 0 requires t(I) == 0 OR t(pI) == 0 (OR both)
 * - Consider counting tables for which the converse is true,
 *   t(I) == 1 AND t(pI) == 1, for any I.  Suppose t(I) == 1 and t(pI) == 1,
 *   for some I.  Then we also have that t(p^2I) == 1, t(p^3I) == 1, ...
 *   So we can partition the inputs into cosets/equivalence classes and
 *   exhaust over possible values of these.
 * - Can compute the total count by inclusion/exclusion or something like that?
 *   e.g. Let C_j be a coset.  Then
 *   N == 2^64 - |Union_j { (# tables with C_j == 1) }|
 */

int transform(int x) {
    int a = 1 & (x >> 5);
    int b = 1 & (x >> 4);
    int c = 1 & (x >> 3);

    return ((x & 0x1f) << 1) | (a ^ (b & c));
}

bool set_1(uint64_t set, uint64_t word, int map[64], int depth, uint64_t *new_set, uint64_t *new_word) {
    // set current depth bit to 1
    set |= 1l << depth;
    word |= 1l << depth;

    int target = map[depth];
    if(1 & (set >> target)) { // target bit already set, make sure it's zero
        if(1 & (word >> target)) {
            return false;
        }
    } else {
        // set target bit to zero
        set |= 1l << target;
        word &= ~(1l << target);
    }

    *new_set = set;
    *new_word = word;
    return true;
}

bool set_0(uint64_t set, uint64_t word, int map[64], int depth, uint64_t *new_set, uint64_t *new_word) {
    // set 0 does not imply anything about target bit

    set |= 1l << depth;
    word &= ~(1l << depth);
    *new_set = set;
    *new_word = word;
    return true;
}

long build(uint64_t set, uint64_t word, int map[64], int depth) {
    long ret = 0;
    if(!(~set)) {
        //printf("valid: %lx\n", word);
        return 1l;
    }

    if(1 & (set >> depth)) {
        ret = build(set, word, map, depth+1);
    } else {
        uint64_t new_set, new_word;
        bool okay = set_1(set, word, map, depth, &new_set, &new_word);

        if(okay) {
            ret += build(new_set, new_word, map, depth+1);
        }

        set_0(set, word, map, depth, &new_set, &new_word);

        // always okay
        ret += build(new_set, new_word, map, depth+1);
    }

    return ret;
}

int main(void) {
    int map[64];
    int i;

    for(i = 0; i < 64; i++) {
        map[i] = transform(i);
    }

    int n_cycles = 0;
    unsigned char cycle_ind[64];
    memset(cycle_ind, 0xff, sizeof(cycle_ind));
    for(i = 0; i < 64; i++) {
        if(cycle_ind[i] != 0xff)
            continue;

        cycle_ind[i] = (unsigned char) n_cycles;
        int j = map[i];
        printf("cycle %d: %2d => %2d", n_cycles, i, j);
        while(j != i) {
            cycle_ind[j] = (unsigned char) n_cycles;
            j = map[j];
            printf(" => %2d", j);
        }
        printf("\n");

        n_cycles++;
    }

    for(i = 0; i < 64; i++) {
        printf("H(%d) == %d (cycle index %d)\n", i , map[i], (int) cycle_ind[i]);
    }

    //long count = build(0, 0, map, 0);

    //printf("result: %ld\n", count);
    return 0;
}
