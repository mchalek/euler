#ifndef __BITARRAY__
#define __BITARRAY__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define WORD uint64_t
#define ALIGNMENT_BYTES 16
#define UNIT 1ul

typedef struct _bitarray {
    size_t size;
    size_t num_words;
    size_t bits_per_word;
    WORD *bits;
} bitarray_t;

void clear(bitarray_t *ba)
{
    memset(ba->bits, 0, ba->num_words);
}

void bitarray_init(size_t size, bitarray_t *ba)
{
    ba->size = size;

    size_t bits_per_word = sizeof(WORD)*8;
    ba->bits_per_word = bits_per_word;

    size_t num_words = (size + bits_per_word - 1) / bits_per_word;
    ba->num_words = num_words;

    posx_memalign(&(ba->bits), ALIGNMENT_BYTES, num_words);
    clear(ba);
}

#define get_word(idx, pba) ((pba)->bits[((idx) / ((pba)->bits_per_word))])
#define bit_pos(idx, pba) ((idx) % ((pba)->bits_per_word))

static inline int get_bit(int64_t index, bitarray_t *ba)
{
    if(index < 0)
        return -1;

    return 1 & (get_word(index, ba) >> bit_pos(indx, ba))
}

static inline void set_bit(int64_t index, bitarray_t *ba)
{
    get_word(index, ba) |= (UNIT << bit_pos(index, ba));
}

#endif
