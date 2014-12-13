#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#define N 200
#define N 10000
#define MAX_C ((int) (1.43 * N))
#define TARGET M_PI

typedef struct _d {
    int a, b;
    double fafb;
} d_t;

int cmp(const void *va, const void *vb)
{
    d_t *a = (d_t *) va;
    d_t *b = (d_t *) vb;

    if(a->fafb == b->fafb)
        return 0;

    return 2*(a->fafb > b->fafb) - 1;
}

d_t *find_closest(double x, d_t *pairs, int left, int right)
{
    if(left == right) {
        return pairs + left;
    }

    if(left + 1 == right) {
        if(fabs(x - pairs[left].fafb) < fabs(x - pairs[right].fafb))
            return pairs + left;
        else
            return pairs + right;
    }

    int mid = (left + right) / 2;

    double dmid = x - pairs[mid].fafb;
    //printf("mid_distance[%d] == %g\n", mid, dmid);

    if(dmid == 0.0)
        return pairs + mid;

    if(dmid < 0)
        return find_closest(x, pairs, left, mid);

    if(dmid > 0)
        return find_closest(x, pairs, mid, right);

    return NULL;
}

int main()
{
    double *f = malloc(MAX_C*sizeof(double));
    int i;
    for(i = 0; i < MAX_C; i++) {
        f[i] = exp(((double) i) / N) - 1;
    }

    int n_pairs = (MAX_C*(MAX_C + 1)) / 2;
    d_t *pairs = malloc(n_pairs * sizeof(d_t));
    int k = 0;
    for(i = 0; i < MAX_C; i++) {
        int j;
        double fi = f[i];
        for(j = 0; j <= i; j++) {
            pairs[k].a = i;
            pairs[k].b = j;
            pairs[k].fafb = fi + f[j];
            k++;
        }
    }

    qsort(pairs, n_pairs, sizeof(d_t), cmp);

    for(i = 0; i < 100; i += 10) {
        printf("pairs[%d]: %d, %d, %g\n", i, pairs[i].a, pairs[i].b, pairs[i].fafb);
    }

    double min_dist = 20.0;
    int abcd[4] = {0, 0, 0, 0};

    for(i = 0; i < n_pairs; i++) {
        double remainder = TARGET - pairs[i].fafb;

        d_t *best = find_closest(remainder, pairs, 0, n_pairs - 1);

        double dist = fabs(pairs[i].fafb + best->fafb - TARGET);

        if(dist < min_dist) {
            min_dist = dist;
            abcd[0] = pairs[i].a;
            abcd[1] = pairs[i].b;
            abcd[2] = best->a;
            abcd[3] = best->b;
        }
    }

    int a = abcd[0];
    int b = abcd[1];
    int c = abcd[2];
    int d = abcd[3];
    printf("best solution at (%d, %d, %d, %d) => %g\n", abcd[0], abcd[1], abcd[2], abcd[3], min_dist);
    printf("result: %d\n", a*a + b*b + c*c + d*d);

    return 0;
}
