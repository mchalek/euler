#include <prime.h>
#include <stdlib.h>
#include <stdio.h>

// NOTE TO SELF: this approach is completely useless!  must account for use
// of primes > 100 in conjunction with some below 100

//#define MAX_N 10000000000000000L
#define MAX_N 1000

long num_products(int num_p, long ind[], long p[])
{
    long result = 0l;
    switch(num_p) {
        case 1: {
                long p0 = p[ind[0]];
                long pp0 = p0;
                while(pp0 < MAX_N) {
                    printf("valid product [%ld]: %ld\n", p0, pp0);
                    result++;
                    pp0 *= p0;
                }
            }
            break;
        case 2: {
                long p0 = p[ind[0]];
                long p1 = p[ind[1]];
                long pp0 = p0;
                while(pp0 < MAX_N) {
                    long product = pp0*p1;

                    if(product >= MAX_N)
                        break;

                    while(product < MAX_N) {
                        printf("valid product [%ld %ld]: %ld\n", p0, p1, product);
                        result++;

                        product *= p1;
                    }

                    pp0 *= p0;
                }
            }
            break;
        case 3: {
                long p0 = p[ind[0]], p1 = p[ind[1]], p2 = p[ind[2]];
                long pp0 = p0;

                while(pp0 < MAX_N) {
                    long pp1 = pp0 * p1;

                    if(pp1 >= MAX_N)
                        break;

                    while(pp1 < MAX_N) {
                        long product = pp1 * p2;

                        if(product >= MAX_N)
                            break;

                        while(product < MAX_N) {
                            printf("valid product [%ld %ld %ld]: %ld\n", p0, p1, p2, product);
                            result++;

                            product *= p2;
                        }

                        pp1 *= p1;
                    }

                    pp0 *= p0;
                }
            }
            break;
    }

    return result;
}

long count(int depth, int max_depth, long cur_ind[], long cur_product, long p[], long np)
{
    if(depth == max_depth) {
        return num_products(depth, cur_ind, p);
    }

    long result = 0l;

    int i;
    int min_ind = depth ? (1 + cur_ind[depth-1]) : 0;

    for(i = min_ind; i < np; i++) {
        cur_ind[depth] = i;

        result += count(1 + depth, max_depth, cur_ind, cur_product * p[i], p, np);
    }

    return result;
}

long solve()
{
    long *p, np;
    primes(1000, &p, &np);

    long ind[3];
    
    long total = 1 + np - 25; // count the number 1, plus primes between 100 and 1000
    total += count(0, 1, ind, 1l, p, 25);
    total += count(0, 2, ind, 1l, p, 25);
    total += count(0, 3, ind, 1l, p, 25);

    return total;
}

int main(void)
{
    long z = solve();

    printf("solution: %ld\n", z);

    return 0;
}
