#include <stdio.h>
#include <kmbits.h>
#include <stdlib.h>
#include <string.h>

#define ALL_DIGIT_MASK ((1 << 10) - 1)
//#define __DEBUG__

long largest_cp = -1;

long factorial(long n) {
    if(!n) {
        return 1L;
    }

    return n * factorial(n-1);
}

int mask_to_digits(int mask, int digits[]) {
    int ndig = 0;
    int i;
    for(i = 0; i < 10; i++) {
        const int bit = (1 << i);
        if(mask & bit) {
            digits[ndig++] = i;
        }
    }

    return ndig;
}

void _build_perms(int ndig, int digits[], int perm, int used_mask, long *n_perms, int perms[]) {
    if(used_mask == ((1 << ndig) - 1)) {
        perms[(*n_perms)++] = perm;
        return;
    }

    int i;
    for(i = 0; i < ndig; i++) {
        const int bit = (1 << i);
        if(used_mask & bit) {
            continue;
        }

        if(!used_mask && !digits[i]) {
            continue;
        }

        _build_perms(ndig, digits, perm * 10 + digits[i], used_mask | bit, n_perms, perms);
    }
}

long build_perms(int mask, int **perms) {
    int digits[10];
    int num_digits = mask_to_digits(mask, digits);

    *perms = malloc(factorial(num_digits) * sizeof(int));

    long num_perms = 0;
    _build_perms(num_digits, digits, 0, 0, &num_perms, *perms);

    return num_perms;
}

void get_mask_and_leading_digit(int x, int *mask, int *leading_digit) {
    *mask = 0;
    *leading_digit = 0;
    while(x) {
        *leading_digit = x % 10;
        int bit = 1 << (*leading_digit);
        x /= 10;

        if((*mask) & bit) {
            *leading_digit = -1;
            *mask = -1;
        }
        (*mask) |= bit;
    }
}

long append(long n, long x) {
    int tmp = x;
    while(tmp) {
        n *= 10;
        tmp /= 10;
    }

    return n + x;
}

long build_biggest_product(long products[]) {
    int i;
    long result = 0;
    for(i = 9; i >= 0; i--) {
        if(products[i]) {
            result = append(result, products[i]);
        }
    }

    return result;
}

void evaluate_concatenations(
        const int A,
        const int k,
        const int maskB[],
        int B[],
        const int i,
        const int product_mask,
        long products[]) {
    if(i == k) {
        if(product_mask != ALL_DIGIT_MASK) {
            // Did not construct full pandigital
            return;
        }

        long max = build_biggest_product(products);
        largest_cp = (largest_cp < max) ? max : largest_cp;

#ifdef __DEBUG__
        printf("CP(%d | %d", A, B[0]);
        int j;
        for(j = 1; j < k; j++) {
            printf("; %d", B[j]);
        }
        printf(") == %ld\n  products: ", max);

        for(j = 9; j >= 0; j--) {
            if(products[j]) {
                printf("%ld ", products[j]);
            }
        }
        printf("\n");

        if(product_mask != ALL_DIGIT_MASK) {
            printf("ERROR: product_mask %x != %x\n", product_mask, ALL_DIGIT_MASK);
        }

#endif
        return;
    }

    int *perm_B = NULL;
    long npermB = build_perms(maskB[i], &perm_B);

    long j;
    for(j = 0; j < npermB; j++) {
        B[i] = perm_B[j];
        long AB = A * B[i];

        int maskAB = 0;
        int leading_digit_AB = 0;

        get_mask_and_leading_digit(AB, &maskAB, &leading_digit_AB);
        if(-1 == maskAB) {
            continue;
        }

        if(maskAB & product_mask) {
            continue;
        }

        // store product by leading digit, for easy generation of largest
        // concatenation
        products[leading_digit_AB] = AB;

        evaluate_concatenations(A, k, maskB, B, 1 + i, product_mask | maskAB, products);

        // erase this product
        products[leading_digit_AB] = 0;
    }

    free(perm_B);

}

void evaluate_masks(int maskA, int k, int maskB[]) {
    long products[10];
    memset(products, 0, sizeof(products));
    int B[10];

    long i;
    int *perm_A = NULL;
    long npermA = build_perms(maskA, &perm_A);
    for(i = 0; i < npermA; i++) {
        int A = perm_A[i];

        evaluate_concatenations(A, k, maskB, B, 0, 0, products);
    }

    free(perm_A);
}

void build_all(int digits_used_mask, int maskA, int k, int maskB[]) {
    if(digits_used_mask == ALL_DIGIT_MASK) {
        if(k < 2) {
            // need 2 or more B's
            return;
        }

        evaluate_masks(maskA, k, maskB);
        return;
    }

    // require that the mask of this B is greater than that of the previous B;
    // this ensures we don't redo work
    int min_this_maskB = k ? (1 + maskB[k-1]) : 2;
    int this_maskB;
    for(this_maskB = min_this_maskB; this_maskB <= ALL_DIGIT_MASK; this_maskB++) {
        if(this_maskB & digits_used_mask) {
            continue;
        }

        maskB[k] = this_maskB;
        build_all(digits_used_mask | this_maskB, maskA, 1 + k, maskB);
    }

    return;
}

int main(void) {
    int maskA;
    int maskB[9];
    for(maskA = 2; maskA <= ALL_DIGIT_MASK; maskA++) {
        if(_popcnt(maskA) > 7) {
            continue;
        }

        build_all(maskA, maskA, 0, maskB);
    }

    printf("Largest concatenated product: %ld\n", largest_cp);
}
