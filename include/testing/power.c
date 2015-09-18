#include <uipow.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 4) {
        printf("SYNTAX: %s a b modulus\n", argv[0]);
        printf("  Returns a^b %% modulus\n");
        exit(-1);
    }

    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    long modulus = strtol(argv[3], NULL, 10);

    long x = uipow(a, b, modulus);

    printf("%ld ^ %ld == %ld mod %ld\n", a, b, x, modulus);

    return 0;
}
