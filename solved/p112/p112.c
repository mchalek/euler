#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define STOP_PCT 99

// used BCD to represent n, quite unnecessary as it turns out

inline uint64_t extract(uint64_t n) {
    uint64_t mul = 1;
    uint64_t result = 0;

    while(n) {
        result += mul*(n & 0xf);
        n >>= 4;
        mul *= 10;
    }

    return result;
}

inline bool stop(uint64_t c, uint64_t n) {
    return c*100 == extract(n)*STOP_PCT;
}

inline bool is_bouncy(uint64_t n) {
    bool dec = false, inc = false;
    uint8_t d1 = n & 0xf;
    while((n >> 4) && !(dec && inc)) {
        uint8_t d0 = d1;
        n >>= 4;
        d1 = n & 0xf;

        dec |= (d1 > d0);
        inc |= (d1 < d0);
    }

    return dec && inc;
}

uint64_t increment(uint64_t n) {
    uint64_t d0 = (n & 0xf) + 1;

    if(d0 == 10)
        return increment(n >> 4) << 4;
    else
        return ((n & (~0xfL)) | d0);
}

int main(void) {
    uint64_t n = 1;
    uint64_t count = 0;

    int k = 0;
    while(!stop(count, n)) {
        n = increment(n);
        count += is_bouncy(n);
    }

    printf("n == %lx, c == %ld\n", n, count);
    return 0;
}
