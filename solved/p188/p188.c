#include <stdio.h>
#include <stdint.h>
#include <uipow.h>

#define A 1777
#define N 1855
#define MODULUS 100000000

uint64_t hyperx(uint64_t a, uint64_t n, uint64_t modulus)
{
    uint64_t i;
    uint64_t ret = a;
    for(i = 1; i < n; i++) {
        ret = uipow(a, ret, modulus);
    }

    return ret;
}

int main()
{
    printf("%d || %d == %ld\n", 3, 2, hyperx(3, 2, MODULUS));
    printf("%d || %d == %ld\n", 3, 3, hyperx(3, 3, MODULUS));
    printf("%d || %d == %ld\n", A, N, hyperx(A, N, MODULUS));

    return 0;
}
