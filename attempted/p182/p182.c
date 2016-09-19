#include <stdio.h>
#include <stdlib.h>
#include <prime.h>

#if 0
#define pp 19
#define qq 37
#else
#define pp 1009
#define qq 3643
#endif

#define phi ((pp-1)*(qq-1))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int *order_p = NULL;
int *order_q = NULL;
int *unconcealed_count = NULL;
int *valid_e = NULL;

int compute_order(int x, int modulus) {
    int result = 1;
    int n = x;

    while(n != 1) {
        result++;
        n *= x;
        n %= modulus;
    }

    return result;
}

void fill_orders(int modulus, int *out) {
    int i;
    for(i = 1; i < modulus; i++) {
        out[i] = compute_order(i, modulus);
    }
}

void determine_valid_e() {
    valid_e = calloc(phi, sizeof(int));
    int e;
    for(e = 1; e < phi; e++) {
        valid_e[e] = 1;
    }

    // e must be coprime to phi.  Assemble primes up to max of p and q
    // and then mark as invalid all e's that share a prime with (p-1) or (q-1)
    long *p;
    long np;
    primes(MAX(pp, qq), &p, &np);

    long ip;

    for(ip = 0; ip < np; ip++) {
        long factor = p[ip];
        if(((pp-1) % factor) && ((qq-1) % factor)) {
            continue;
        }

        long bad_e = factor;
        while(bad_e < phi) {
            valid_e[bad_e] = 0;
            bad_e += factor;
        }
    }
}

void init() {

    determine_valid_e();

    order_p = calloc(pp, sizeof(int));
    fill_orders(pp, order_p);

    order_q = calloc(qq, sizeof(int));
    fill_orders(qq, order_q);

    unconcealed_count = calloc(phi, sizeof(int));
}

int lcm(int m, int n) {
    int i = n;
    while(i % m) {
        i += n;
    }

    return i;
}

void compute_unconcealed(int m) {
    int mpp = m % pp;
    int mqq = m % qq;

    if(!mpp || !mqq) {
        return;
    }

    int ep = order_p[mpp];
    int eq = order_q[mqq];

    int e = lcm(ep, eq);

    //printf("O[%d] == %d\n", m, e);

    int i;
    for(i = e + 1; i < phi; i += e) {
        //printf("%d ^ %d == %d mod %d\n", m, i, m, pp*qq);
        unconcealed_count[i]++;
    }
}

int min_unconcealed() {
    int e;
    int result = pp*qq;
    for(e = 2; e < phi; e++) {
        if(unconcealed_count[e] < result && valid_e[e]) {
            result = unconcealed_count[e];
        }
    }

    return result;
}

int main(void) {
    init();

    int m;
    for(m = 1; m < (pp*qq); m++) {
        compute_unconcealed(m);
    }
    
    int mu = min_unconcealed();
    //printf("min unconcealed count: %d\n", mu);

    int e;
    long Se = 0l;
    for(e = 2; e < phi; e++) {
        //printf("unconcealed_count[%d]: %d\n", e, unconcealed_count[e]);

        if(unconcealed_count[e] == mu && valid_e[e]) {
            //printf("e == %4d achieves minimum unconcealed count of %d\n", e, mu);
            Se += e;
        }
    }

    printf("result: %ld\n", Se);
}

