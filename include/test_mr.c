#include "miller_rabin.h"

int main(void) {
    int x;
    for(x = 13; x < 300; x++) {
        printf("mr(%d): %d\n", x, mr_isprime(x));
    }

    return 0;
}
