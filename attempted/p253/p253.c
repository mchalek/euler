#include <stdio.h>
#include <kmbits.h>

static inline int count_pieces(uint64_t config) {
    int result = 0;
    while(config) {
        result++;
        config >>= _trailz(config);
        config >>= _trailz(~config);
    }

    return result;
}

int main(void) {
    printf("pieces %lx == %d\n", 0xffaaccbbddl, count_pieces(0xffaaccbbddl));
    
    return 0;
}
