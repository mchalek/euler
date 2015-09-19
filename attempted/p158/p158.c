#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

long factorial(int n, int k) {
    long result = 1;
    for(; k; k--) {
        result *= n;
        n--;
    }

    return result;
}

long nchoosek(long n, int k) {
    k = (n - k < k) ? (n - k) : k;
    return factorial(n, k)/factorial(k, k);
}

typedef struct {
    uint32_t mask;
    int terminal;
    long count_with[26];
    long count_without[26];
} counts_t;

int _efd(int num_bits, int remaining, int min_bit, uint32_t current, int *count, counts_t *items, bool invert) {
    // generate all bit fields of length num_bits and density given by
    // the initial value of the remaining field.
    // Accumulate those in the items array, which must be pre-allocated to
    // the correct size (num_bits choose density)
    
    if(!remaining) {
        memset(items + *count, 0, sizeof(counts_t));
        if(invert)
            current ^= ((1 << num_bits) - 1);

        items[*count].mask = current;
        (*count)++;
        return 1;
    }

    int pos;
    int result = 0;
    for(pos = min_bit; pos < num_bits; pos++) {
        uint32_t bit = 1 << pos;
        if(current & bit)
            continue;
        
        result += _efd(num_bits, remaining - 1, 
                pos + 1, current ^ bit, count, items, invert);
    }

    return result;
}

int exhaust_fixed_density(int num_bits, int density, counts_t *items) {
    int num_hits = 0;
    
    if(num_bits - density < density) {
        return _efd(num_bits, num_bits-density, 0, 0, &num_hits, items, true);
    } else {
        return _efd(num_bits, density, 0, 0, &num_hits, items, false);
    }
}

int main(void) {
    int density = 16;
    int expected = nchoosek(26, density);
    printf("expected items: %d\n", expected);
    counts_t *items = calloc(expected, sizeof(counts_t));

    int num_items = exhaust_fixed_density(26, density, items);

    printf("items generated: %d\n", num_items);

    return 0;
}
