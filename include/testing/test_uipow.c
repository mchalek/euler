#include <uipow.h>
#include <stdio.h>

int main() {
    // use a big-modulus example
    uint64_t x = 1482841199L;
    uint64_t y = 319225L;
    
    uint64_t modulus = 5230182401L;

    uint64_t test = uipow(x, y, modulus);

    if(test != 4028785180L) {
        printf("FAIL!\n");
    } else {
        printf("SUCCESS!\n");
    }

    printf("uipow computed: %ld^%ld == %ld mod %ld\n", 
            x, y, test, modulus);

    return 0;
}
