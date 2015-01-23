#include <stdio.h>
#include <stdlib.h>
#include <prime.h>

#define MIN_K 2
#define MAX_K 12000
#define MAX_I 14000

//#define __DEBUG

typedef struct _sc {
    int sum;
    int count;
} sumcount_t;

typedef struct _ds {
    int nsum;
    sumcount_t *sums;
} dsum_t;

int max_count(dsum_t *ds, int n, long ndiv, long div[]) 
{
    int ret = 0;
    int i;
    for(i = 0; i < ndiv; i++) {
        long d = div[i];
        if(d == 1)
            continue;

        if(d == n)
            ret++;
        else
            ret += ds[n / d].nsum;
    }

    return ret;
}

int cmp(const void *va, const void *vb)
{
    const sumcount_t *a = va;
    const sumcount_t *b = vb;

    if(a->sum == b->sum) {
        return a->count - b->count;
    } else {
        return a->sum - b->sum;
    }
}

void dedupe(int *n, sumcount_t *items)
{
    qsort(items, *n, sizeof(sumcount_t), cmp);

    int i, j;
    j = 1;
    for(i = 1; i < *n; i++) {
        if(cmp(items + i, items + j - 1)) {
            items[j++] = items[i];
        }
    }

    *n = j;
}

void insert(dsum_t *ds, int n, long ndiv, long div[]) {
    sumcount_t *tmp = malloc(max_count(ds, n, ndiv, div) * sizeof(sumcount_t));
    int c = 0;
    int i;
    for(i = 0; i < ndiv; i++) {
        long d = div[i];
        if(d == 1)
            continue;

        if(d == n) {
            tmp[c].sum = n;
            tmp[c++].count = 1;
        } else {
            int rem = n / d;
            int j;
            for(j = 0; j < ds[rem].nsum; j++) {
                tmp[c].sum = d + ds[rem].sums[j].sum;
                tmp[c++].count = 1 + ds[rem].sums[j].count;
            }
        }
    }

    dedupe(&c, tmp);

    ds[n].nsum = c;
    ds[n].sums = realloc(tmp, c*sizeof(sumcount_t));

#ifdef __DEBUG
    printf("sums for n == %d: ", n);
    for(i = 0; i < c; i++) {
        printf("(%d, %d)  ", ds[n].sums[i].sum, ds[n].sums[i].count);
    }
    printf("\n");
#endif
}

int main()
{
    long *p, np;
    primes(MAX_I, &p, &np);

    dsum_t *ds = calloc(1 + MAX_I, sizeof(dsum_t));

    ds[1].nsum = 0;
    ds[1].sums = malloc(sizeof(sumcount_t));
    ds[1].sums[0].sum = 0;
    ds[1].sums[0].count = 0;

    int *mps = calloc(1 + MAX_K, sizeof(int));

    int i;
    int filled = 0;
    for(i = 2; i <= MAX_I && filled < MAX_K - MIN_K + 1; i++) {
        long f[20], e[20];
        long nf;
        factor(i, p, np, &nf, f, e);

        long nd, *div;
        divisors(nf, f, e, &nd, &div);

        insert(ds, i, nd, div);

        int j;
        for(j = 0; j < ds[i].nsum; j++) {
            int k = i - ds[i].sums[j].sum + ds[i].sums[j].count;

            if(k < MIN_K || k > MAX_K)
                continue;

            if(!mps[k]) {
                mps[k] = i;
                filled++;

            }
        }
    }

    for(i = MIN_K; i <= MAX_K; i++)
        printf("k == %d: %d\n", i, mps[i]);

    return 0;
}
