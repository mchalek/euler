#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 60000000
#define maxD 1000

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
        factors[i].factors = realloc(factors[i].factors, factors[i].nf * sizeof(int [2]));
    }

}

void merge(factor_t a, factor_t b, factor_t *m) {
    memset(m -> factors, 0, 10*sizeof(int [2]));
    m -> nf = 0;

    int i;
    for(i = 0; i < a.nf; i++) {
        int ind = m -> nf++;
        m -> factors[ind][0] = a.factors[i][0];
        m -> factors[ind][1] = a.factors[i][1];
    }

    // get shared factors
    for(i = 0; i < b.nf; i++) {
        int j;
        char done = 0;
        for(j = 0; j < m -> nf; j++) {
            if(m -> factors[j][0] == b.factors[i][0]) {
                m -> factors[j][1] += b.factors[i][1];
                done = 1;
                break;
            }
        }

        if(!done) {
            int ind = m -> nf++;
            m -> factors[ind][0] = b.factors[i][0];
            m -> factors[ind][1] = b.factors[i][1];
        }
    }
}

int ipow(int x, int y) {
    if(!y)
        return 1;

    return x*ipow(x, y-1);
}

int build(factor_t a, int x, int x_sol[], int count[], int start, long y) {
    int i;
    int ret = 0;

    if(start == a.nf) {
        long D = (((long) x)*x - 1) / (y*y);
        if(D > 1000)
            return 0;

        printf("%d^2 - %ld %ld^2 == 1\n", x, D, y);

        if(D < maxD) {
            if(!x_sol[D]) {
                x_sol[D] = x;
                ret = 1;
            }
        }

        return ret;
    }

    for(i = 0; i <= a.factors[start][1]; i += 2) {
        count[start] = i;
        ret += build(a, x, x_sol, count, start+1, y*ipow(a.factors[start][0], i/2));
    }
    count[start] = 0;

    return ret;
}

int main(void) {
    factor();
    
    int *x_sol = calloc(maxD, sizeof(int));
    int x, nD = 0;

    factor_t merged;
    merged.factors = calloc(10, sizeof(int [2]));
    merged.nf = 0;

    int zeros[10];
    memset(zeros, 0, sizeof(zeros));

    x = 1;
    while(nD < 1000) {
        x++;
        if(x + 1 >= N) {
            printf("complete solution not found.  Increase N and try again.\n");
            break;
        }

        merge(factors[x-1], factors[x+1], &merged);
        nD += build(merged, x, x_sol, zeros, 0, 1);

#if 0
        printf("merged factors for (%d - 1) * (%d + 1): ", x, x);
        int i;
        for(i = 0; i < merged.nf; i++) {
            printf("%d^%d  ", merged.factors[i][0], merged.factors[i][1]);
        }
        printf("\n");
#endif
    }

    printf("found %d solutions\n", nD);
    int D;
    for(D = 2; D < 20; D++) {
        printf("x(%d) == %d\n", D, x_sol[D]);
    }

    return 0;
}
