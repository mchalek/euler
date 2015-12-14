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

    posix_memalign((void **) &(ba->bits), ALIGNMENT_BYTES, num_words);
    clear(ba);
}

#define GET_WORD(idx, pba) ((pba)->bits[(idx) / ((pba)->bits_per_word)])
#define BIT_POS(idx, pba) ((idx) % ((pba)->bits_per_word))

static inline int get_bit(int64_t index, bitarray_t *ba)
{
    if(index < 0 || index >= (int64_t) ba->size) {
        // intentionally crash
        ba->bits[ba->size+1000] = 10;
        return -1;
    }

    return 1 & (GET_WORD(index, ba) >> BIT_POS(index, ba));
}

static inline void set_bit(int64_t index, bitarray_t *ba)
{
    GET_WORD(index, ba) |= (UNIT << BIT_POS(index, ba));
}

#endif
