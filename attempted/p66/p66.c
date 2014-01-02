#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 20000000
#define Np 100000 // num primes only need be ~ sqrt(N)
#define maxD 1001

typedef struct {
    int factors[10][2];
    int nf;
} factor_t;

int *primes = NULL;
int np = 0;

int nlogi(int n, int i) {
    int ret = 0;
    if(i == 1)
        return n;

    while(!(n % i)) {
        ret++;
        n /= i;
    }

    return ret;
}

long ipow(long x, long y) {
    int i;
    if(!y)
        return 1;

    long ret = x;
    for(i = 1; i < y; i++)
        ret *= x;

    return ret;
}

void compute_primes() {
    char *iscomposite = calloc(Np, sizeof(char));
    int nalloc = Np / 10;
    np = 0;
    primes = malloc(nalloc*sizeof(int));

    int i;
    for(i = 2; i < Np; i++) {
        if(!iscomposite[i]) {
            primes[np++] = i;

            int j;
            for(j = 2*i; j < Np; j += i)
                iscomposite[j] = 1;

            if(np == nalloc) {
                nalloc *= 2;
                primes = realloc(primes, nalloc*sizeof(int));
            }
        }
    }

    free(iscomposite);
    primes = realloc(primes, np*sizeof(int));
}

void factor(int x, factor_t *f) {
    memset(f -> factors, 0, sizeof(f -> factors));
    f -> nf = 0;

    int i, p;
    for(i = 0; i < np && x > 1; i++) {
        p = primes[i];
        if(p*p > x)
            break;

        if(!(x % p)) {
            int exponent = nlogi(x, p);
            int ind = f -> nf++;

            f -> factors[ind][0] = p;
            f -> factors[ind][1] = exponent;
            x /= ipow(p, exponent);
        }
    }

    if(x > 1) { // residual must be prime
        int ind = f -> nf++;
        f -> factors[ind][0] = x;
        f -> factors[ind][1] = 1;
    }
}

void merge(factor_t a, factor_t b, factor_t *m) {
    int i;
    memcpy(m -> factors, a.factors, sizeof(a.factors));
    m -> nf = a.nf;

    // get shared factors
    for(i = 0; i < b.nf; i++) {
        int j;
        char inserted = 0;
        for(j = 0; j < m -> nf; j++) {
            if(m -> factors[j][0] == b.factors[i][0]) {
                m -> factors[j][1] += b.factors[i][1];
                inserted = 1;
                break;
            }
        }

        if(!inserted) {
            int ind = m -> nf++;
            m -> factors[ind][0] = b.factors[i][0];
            m -> factors[ind][1] = b.factors[i][1];
        }
    }
}

int build(factor_t a, int x, int x_sol[], int start, long D) {
    // finds D, y such that a == D*y^2
    int i;
    int ret = 0;

    if(start == a.nf) {
        if(!x_sol[D]) {
            x_sol[D] = x;
            ret = 1;
        }

        return ret;
    }

    int p = a.factors[start][0];
    int exponent = a.factors[start][1];

    for(i = 0; i <= exponent; i += 2) {
        long new_D = D*ipow(p, exponent - i);
        if(new_D < maxD)
            ret += build(a, x, x_sol, start+1, new_D);
    }

    return ret;
}

int main(void) {
    compute_primes();
    
    int *x_sol = calloc(maxD, sizeof(int));
    int x, nD = 0; // start nD at 32 for the squares

    while(nD*nD < maxD)
        nD++;
    nD--;
    int nsol = nD;

    factor_t a, merged, queue[2];


    x = 1;
    factor(1, queue);
    factor(2, queue+1);
    while(nD < 1000) {
        if(!(x % 10000000)) {
            printf("after x %d, nD == %d\n", x, nD);
        }
        x++;
        if(x + 1 >= N) {
            printf("complete solution not found.  Increase N and try again.\n");
            break;
        }

        a = queue[0];
        queue[0] = queue[1];
        factor(x+1, queue + 1);

        merge(a, queue[1], &merged);

        nD += build(merged, x, x_sol, 0, 1);

#if 0
        printf("merged factors for (%d - 1) * (%d + 1): ", x, x);
        int i;
        for(i = 0; i < merged.nf; i++) {
            printf("%d^%d  ", merged.factors[i][0], merged.factors[i][1]);
        }
        printf("\n");
#endif
    }

    int D;
    int maxx = 0;
    int Dstar = 0;
    for(D = 1; D < maxD; D++) {
        printf("x(%d) == %d\n", D, x_sol[D]);
        if(x_sol[D] > maxx) {
            maxx = x_sol[D];
            Dstar = D;
        }
        if(x_sol[D] != 0)
            nsol++;
    }

    printf("found %d solutions (%d)\n", nD, nsol);
    printf("max at D == %d, x == %d\n", Dstar, maxx);

    return 0;
}
