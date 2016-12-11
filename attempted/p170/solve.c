#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>

long largest_result = -1;

long factorial(long n) {
    if(!n) {
        return 1;
    }

    return n * factorial(n - 1);
}

long ncr(long n, long r) {
    return factorial(n) / (factorial(r) * factorial(n-r));
}

int mask_to_digits(int mask, int digits[]) {
    int ndig = 0;
    int i;
    for(i = 0; i < 10; i++) {
        if((mask >> i) & 1) {
            digits[ndig++] = i;
        }
    }

    return ndig;
}

void build_permutations(int digits_used_mask, int perm, int perm_len, int ndig, int digits[], int *nperm, int permutations[]) {
    if(perm_len == ndig) {
        permutations[(*nperm)++] = perm;
        return;
    }

    int i;
    for(i = 0; i < ndig; i++) {
        int bit = 1 << i;
        if(digits_used_mask & i) {
            continue;
        }

        build_permutations(
                digits_used_mask | bit,
                10 * perm + digits[i],
                1 + perm_len,
                ndig,
                digits,
                nperm,
                permutations);
    }
}

bool test(long product, int *mask_out) {
    *mask_out = 0;
    int mask = 0;
    while(product) {
        int digit = product % 10;
        int bit = 1 << digit;

        if(mask & bit) {
            return false;
        }

        mask |= bit;
        product /= 10;
    }

    return true;
}

void build_from_masks(int ma, int mb, int mc) {
    int dig_a[10];
    int dig_b[10];
    int dig_c[10];

    const int ndig_a = mask_to_digits(ma, dig_a);
    const int ndig_b = mask_to_digits(mb, dig_b);
    const int ndig_c = mask_to_digits(mc, dig_c);

    int n_perm_a = factorial(ndig_a);
    int n_perm_b = factorial(ndig_b);
    int n_perm_c = factorial(ndig_c);

    int *perms_a = malloc(n_perm_a * sizeof(int));
    int *perms_b = malloc(n_perm_b * sizeof(int));
    int *perms_c = malloc(n_perm_c * sizeof(int));

    int n_perm_test_a, n_perm_test_b, n_perm_test_c;

    build_permutations(0, 0, 0, ndig_a, dig_a, &n_perm_test_a, perms_a);
    build_permutations(0, 0, 0, ndig_b, dig_b, &n_perm_test_b, perms_b);
    build_permutations(0, 0, 0, ndig_c, dig_c, &n_perm_test_c, perms_c);

    if(n_perm_test_a != n_perm_a) {
        fprintf(stderr, "ERROR: n_perm_test_a (%d) != n_perm_a (%d)\n", n_perm_test_a, n_perm_a);
        exit(1);
    }
    if(n_perm_test_b != n_perm_b) {
        fprintf(stderr, "ERROR: n_perm_test_b (%d) != n_perm_b (%d)\n", n_perm_test_b, n_perm_b);
        exit(1);
    }
    if(n_perm_test_c != n_perm_c) {
        fprintf(stderr, "ERROR: n_perm_test_c (%d) != n_perm_c (%d)\n", n_perm_test_c, n_perm_c);
        exit(1);
    }

    int a, b, c;
    for(a = 0; a < n_perm_a; a++) {
        int perm_a = perms_a[a];
        for(b = 0; b < n_perm_b; b++) {
            int perm_b = perms_b[b];
            long prod_b = ((long) perm_a) * perm_b;
            int mask_b;

            if(!test(prod_b, &mask_b)) {
                continue;
            }

            for(c = 0; c < n_perm_c; c++) {
                int perm_c = perms_c[c];
                int mask_c;
                long prod_c = ((long) perm_a) * perm_c;

                if(!test(prod_c, &mask_c)) {
                    continue;
                }

                if(mask_b & mask_c) {
                    continue;
                }

                if((mask_b | mask_c) == ((1 << 10) - 1)) {
                    printf("CP(%d | %d; %d): %ld%ld <=> %ld%ld\n", perm_a, perm_b, perm_c, prod_b, prod_c, prod_c, prod_b);
                }
            }
        }
    }

    free(perms_a);
    free(perms_b);
    free(perms_c);
}

int main() {
    int mask_A, mask_B, mask_C;

    for(mask_A = 1; mask_A < (1 << 10); mask_A++) {
        for(mask_B = 1; mask_B < (1 << 10); mask_B++) {
            if(mask_A & mask_B) {
                continue;
            }

            mask_C = ~(mask_A | mask_B) & ((1 << 10) - 1);

            build_from_masks(mask_A, mask_B, mask_C);
        }
    }
    return 0;
}
