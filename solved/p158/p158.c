#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <kmbits.h>

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
    long count_with[26];
    long count_without[26];
} counts_t;

int _efd(int num_bits, int remaining, int min_bit, uint32_t current, int *count, counts_t *items, int index[], bool invert) {
    // generate all bit fields of length num_bits and density given by
    // the initial value of the remaining field.
    // Accumulate those in the items array, which must be pre-allocated to
    // the correct size (num_bits choose density)
    
    if(!remaining) {
        memset(items + *count, 0, sizeof(counts_t));
        if(invert)
            current ^= ((1 << num_bits) - 1);

        index[current] = *count;

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
        
        result += _efd(num_bits, remaining - 1, pos + 1, current ^ bit,
                count, items, index, invert);
    }

    return result;
}

int exhaust_fixed_density(int num_bits, int density, counts_t *items, int index[]) {
    int num_hits = 0;

    int i;
    for(i = 0; i < (1 << num_bits); i++) {
        index[i] = -1;
    }
    
    if(num_bits - density < density) {
        return _efd(num_bits, num_bits-density, 0, 0, &num_hits, items, index, true);
    } else {
        return _efd(num_bits, density, 0, 0, &num_hits, items, index, false);
    }
}

int main(void) {
    int i;
    counts_t *items = calloc(26, sizeof(counts_t));
    int *index = malloc((1 << 26)*sizeof(int));
    int num_items = exhaust_fixed_density(26, 1, items, index);

    for(i = 0; i < num_items; i++) {
        // generation is in order for these, so we are guaranteed that
        // items[i].mask == 1 << i, so that the appropriate index for
        // count_without increment is i.
        items[i].count_without[i] = 1;
    }

    long max_total_count = 0;
    for(i = 1; i < 26; i++) {
        const int density = 1 + i;

        int num_new_items = nchoosek(26, density);
        counts_t *new_items = calloc(num_new_items, sizeof(counts_t));
        int *new_index = malloc((1 << 26) * sizeof(int));
        exhaust_fixed_density(26, density, new_items, new_index);

        int j;
        long total_count = 0;
        for(j = 0; j < num_new_items; j++) {
            // j indexes into the different possible masks at the current
            // density

            const uint32_t mask = new_items[j].mask;
            uint32_t destroyed_mask = mask;
            int tz = _trailz(mask);
            int last_item = tz;
            while(destroyed_mask) {
                destroyed_mask >>= 1 + tz;

                // construct previous mask by removing last_item from current
                // mask
                uint32_t prev_mask = mask ^ (1u << last_item);
                counts_t *prev = items + index[prev_mask];
                int prev_item;
                for(prev_item = 0; prev_item < last_item; prev_item++) {
                    // last_item comes lex after prev_item, so add a hit
                    new_items[j].count_with[last_item] += 
                        prev->count_without[prev_item];
                }

                for(prev_item = 1 + last_item; prev_item < 26; prev_item++) {
                    // last_item comes lex before prev_item, so no hit
                    new_items[j].count_without[last_item] += 
                        prev->count_without[prev_item];
                    new_items[j].count_with[last_item] +=
                        prev->count_with[prev_item];
                }
                    
                tz = _trailz(destroyed_mask);
                last_item += 1 + tz;
            }

            int k;
            for(k = 0; k < 26; k++)
                total_count += new_items[j].count_with[k];
        }

        printf("total count at density %d: %ld\n", density, total_count);

        max_total_count = (total_count > max_total_count) ? total_count : max_total_count;

        free(items);
        free(index);
        items = new_items;
        index = new_index;
    }

    printf("max total count: %ld\n", max_total_count);

    return 0;
}
