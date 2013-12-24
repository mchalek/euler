#include <stdio.h>
#include <stdlib.h>

#define N 1000000
typedef struct {
    int (*factors)[2];
    int nf;
} factor_t;

factor_t *factors = NULL;

int nlogi(int n, int i) {
    if(n % i)
        return 0;

    else return 1 + nlogi(n/i, i);
}

void factor() {
    char *iscomposite = calloc(N, sizeof(char));
    factors = malloc(N*sizeof(factor_t));
    int i;
    for(i = 2; i < N; i++) {
        // 10 primes guaranteed to fit; overflows int32
        factors[i].factors = calloc(10, sizeof(int [2]));
        factors[i].nf = 0;
    }

    for(i = 2; i < N; i++) {
        if(!iscomposite[i]) {
            int k;
            for(k = i; k < N; k += i) {
                int ind = factors[k].nf++;
                factors[k].factors[ind][0] = i;
                factors[k].factors[ind][1] = nlogi(k, i);
                iscomposite[k] = 1;
            }
        }
    }
}

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("SYNTAX: %s x\n", argv[0]);
        exit(0);
    }

    factor();

    int x = atoi(argv[1]);

    printf("%d prime factors of %d: ", factors[x].nf, x);
    int i;
    for(i = 0; i < factors[x].nf; i++) {
        printf("%d^%d  ", factors[x].factors[i][0], factors[x].factors[i][1]);
    }
    printf("\n");

    return 0;
}
