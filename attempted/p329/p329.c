#include <prime.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_CROAKS 15

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define TARGET 0x79da

bool isprime[501];

void reduce(long *num, long *den) {
    // den only can have factors of 2, 3, 5
    while(!((*num) % 2) && !((*den) % 2)) {
        (*num) /= 2;
        (*den) /= 2;
    }

    while(!((*num) % 3) && !((*den) % 3)) {
        (*num) /= 3;
        (*den) /= 3;
    }

    while(!((*num) % 5) && !((*den) % 5)) {
        (*num) /= 5;
        (*den) /= 5;
    }
}

void mul_frac(long a, long b, long *num, long *den) {
#ifdef __DEBUG__
    fprintf(stderr, "%ld / %ld * %ld / %ld == ", a, b, *num, *den);
#endif
    if((*num) % b == 0) {
        *num /= b;
    } else *den *= b;

    if((*den) % a == 0) {
        *den /= a;
    } else *num *= a;
#ifdef __DEBUG__
    fprintf(stderr, "%ld / %ld\n", *num, *den);
#endif
}

void add_frac(long a, long b, long *num, long *den)
{
#ifdef __DEBUG__
    fprintf(stderr, "%ld / %ld + %ld / %ld == ", a, b, *num, *den);
#endif
    // den only can have factors of 2, 3, 5
    long common_denom = 0;
    long test = 2;
    while(!(b % test) || !(*den % test)) {
        test *= 2;
    }

    common_denom = test / 2;

    test = 3;
    while(!(b % test) || !((*den) % test)) {
        test *= 3;
    }

    common_denom *= test / 3;

    test = 5;
    while(!(b % test) || !((*den) % test)) {
        test *= 5;
    }

    common_denom *= test / 5;

    *num = (*num) * (common_denom / (*den)) + a * (common_denom / b);

    *den = common_denom;

    reduce(num, den);

#ifdef __DEBUG__
    fprintf(stderr, "%ld / %ld\n", *num, *den);
#endif
}

void jump(int position, int ncroaks, int path[],
          long path_num, long path_den, long *total_num, long *total_den)
{
    if(ncroaks == NUM_CROAKS) {
        int i;
        for(i = 0; i < NUM_CROAKS; i++) {
            bool P = TARGET & (1l << (NUM_CROAKS - 1 - i));

            if(P) {
                if(isprime[path[i]]) {
                    mul_frac(2, 3, &path_num, &path_den);
                } else {
                    mul_frac(1, 3, &path_num, &path_den);
                }
            } else {
                if(isprime[path[i]]) {
                    mul_frac(1, 3, &path_num, &path_den);
                } else {
                    mul_frac(2, 3, &path_num, &path_den);
                }
            }
        }

        add_frac(path_num, path_den, total_num, total_den);

        return;
    }

    path[ncroaks] = position;
    if(position == 1) {
        jump(position+1, 1+ncroaks, path, path_num, path_den, total_num, total_den);
    } else if(position == 500) {
        jump(position-1, 1+ncroaks, path, path_num, path_den, total_num, total_den);
    } else {
        mul_frac(1, 2, &path_num, &path_den);

        jump(position-1, 1+ncroaks, path, path_num, path_den, total_num, total_den);
        jump(position+1, 1+ncroaks, path, path_num, path_den, total_num, total_den);
    }
}

void init() {
    long *p, np;
    primes(500, &p, &np);

    memset(isprime, 0, sizeof(isprime));
    int i;

    for(i = 0; i < np; i++)
        isprime[p[i]] = true;

    free(p);
}

int main(void)
{
    init();

    long path_num = 1;
    long path_den = 500;
    long total_num = 0;
    long total_den = 1;

    int i;
    int path[16];
    for(i = 1; i <= 500; i++) {
        printf("doing i == %d\n", i);
        jump(i, 0, path, path_num, path_den, &total_num, &total_den);

        printf("%ld / %ld\n", total_num, total_den);
    }

    printf("solution: %ld/%ld\n", total_num, total_den);

    return 0;
}
