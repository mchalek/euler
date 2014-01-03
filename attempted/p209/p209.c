#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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
        printf("H(%d) == %d\n", i , map[i]);
    }

    long count = build(0, 0, map, 0);

    printf("result: %ld\n", count);
    return 0;
}
