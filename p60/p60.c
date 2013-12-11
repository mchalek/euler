#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int reverse(int x) {
    int ret = 0;
    while(x) {
        ret *= 10;
        ret += x % 10;
        x /= 10;
    }
        
    return ret;
}

void primes(int N, int **p, int *nprimes) {
    char *isc = calloc(N, sizeof(char));
    int *_p = malloc(N*sizeof(int));
    int np = 0;
    int i;

    for(i = 2; i < N; i++) {
        if(!isc[i]) {
            _p[np++] = i;
            int j;
            for(j = 2*i; j < N; j += i)
                isc[j] = 1;
        }
    }

    *p = realloc(_p, np*sizeof(int));
    *nprimes = np;

    free(isc);
}

int isprime(int x, int *pr, int npr)
{ 
    int i;
    if(x == 1)
        return 0;

    if(x > ((long) pr[npr-1])*pr[npr-1]) {
        printf("Can't check that!  %d\n", x);
        exit(0);
    }

    for(i = 0; (i < npr) ? pr[i]*pr[i] <= x : 0; i++)
        if(!(x % pr[i]))
            return 0;

    return 1;
}

int concat(int a, int b) {
    int i = 1;
    while(b / i) i *= 10;

    return a*i + b;
}

void get_combos(int x, int (**comb)[2], int *ncomb, int *pr, int npr, bool reversed) {
    int i = 10;
    int y = reversed ? reverse(x) : x;
    while(y / i) { 
        int a = reversed ? reverse(y / i) : y / i;
        int b = reversed ? reverse(y % i) : y % i;
        i *= 10;

        if(isprime(a, pr, npr) && 
           isprime(b, pr, npr) && 
           isprime(concat(a, b), pr, npr) && 
           isprime(concat(b, a), pr, npr)) {
            //printf("combo: %d/%d\n", MIN(a, b), MAX(a,b));
            int c[] = {MIN(a, b), MAX(a, b)};
            memcpy(&((*comb)[(*ncomb)++]), c, 2*sizeof(int)); 
        }
    }
}

void combos(int *pr, int npr, int (**comb)[2], int *ncomb) {
    int i;
    for(i = 0; i < npr; i++) {
        get_combos(pr[i], comb, ncomb, pr, npr, false);
        get_combos(pr[i], comb, ncomb, pr, npr, true);
    }
}

int cmp(const void *va, const void *vb) {
   int a0 = *((int *) va);
   int b0 = *((int *) vb);

   if(a0 == b0) {
       int a1 = *(((int *) va) + 1);
       int b1 = *(((int *) vb) + 1);

       return a1 - b1;
   }  else 
       return a0 - b0;
}

void uniq(int (*x)[2], int *nx) {
    int ny = 0;
    int ac = 0, bc = 0;
    int i;

    for(i = 0; i < *nx; i++) {
        int a = x[i][0];
        int b = x[i][1];

        if(ac != a || bc != b) {
            x[ny][0] = a;
            x[ny][1] = b;
            ny++;
            ac = a;
            bc = b;
        }
    }

    *nx = ny;
}

typedef struct _group_t {
    int Nb;
    int *b;
} group_t;

void group(int (*comb)[2], int ncombos, group_t *g, int N) {
    int *total_counts = calloc(N, sizeof(int));
    int i;
    for(i = 0; i < ncombos; i++) {
        int a = comb[i][0];
        int b = comb[i][1];
        total_counts[a]++;
        total_counts[b]++;
    }

    for(i = 0; i < N; i++) {
        g[i].b = malloc(total_counts[i]*sizeof(int));
        g[i].Nb = 0;
    }
    free(total_counts);

    for(i = 0; i < ncombos; i++) {
        int a = comb[i][0];
        int b = comb[i][1];

        g[a].b[g[a].Nb++] = b;
        g[b].b[g[b].Nb++] = a;
    }
}

int duped(int chain[], int depth) {
    int i, j;
    for(i = 0; i < depth; i++)
        for(j = i+2; j < depth; j++)
            if(chain[i] == chain[j])
                return 1;
    return 0;
}

int concatenable(int chain[], int depth, int *pr, int npr) {
    int i, j;

    for(i = 0; i < depth; i++)
        for(j = i+2; j < depth; j++) {
            int c0 = concat(chain[i], chain[j]);
            if(!isprime(c0, pr, npr))
                return 0;

            int c1 = concat(chain[j], chain[i]);
            if(!isprime(c1, pr, npr))
                return 0;
        }

    return 1;
}

int check(int chain[], int depth, int *pr, int npr) {
    if(duped(chain, depth))
        return 0;

    return concatenable(chain, depth, pr, npr);
}

void traverse(int start, int depth, int max_depth, int sum, int *best, int *chain, group_t *gp, int N, int *pr, int npr) {
    if(sum > *best)
        return;

    if(depth == max_depth) {
        *best = sum;
        printf("valid chain!  ");
        int i;
        for(i = 0; i < max_depth; i++) {
            printf("%d", chain[i]);
            if(i < max_depth-1)
                printf(", ");
        }
        printf(" <- %d\n", sum);
        return;
    }

    int i;
    if(start >= N) {
        printf("Error!! start (%d) > N (%d)\n", start, N);
        exit(0);
    }

    for(i = 0; i < gp[start].Nb; i++) {
        int next = gp[start].b[i];
        chain[depth] = next;
        if(!check(chain, depth+1, pr, npr))
            continue;

        traverse(next, depth+1, max_depth, sum + next, best, chain, gp, N, pr, npr);
    }
}

void revise(group_t **pgp, int *N, int Nmax, int Nmin) {
    *pgp = realloc(*pgp, Nmax*sizeof(group_t));
    group_t *gp = *pgp;

    int i;

    for(i = 0; i < Nmax; i++) {
        int j;
        int k = 0;

        for(j = 0; j < gp[i].Nb; j++) {
            if(gp[i].b[j] < Nmax && gp[i].b[j] > Nmin) {
                gp[i].b[k++] = gp[i].b[j];
            }
        }
        gp[i].Nb = k;
        gp[i].b = realloc(gp[i].b, k*sizeof(int));
    }
    *N = Nmax;
}

int min_chain_sum(int max_depth, group_t *gp, int N, int *pr, int npr) {
    int i, j;
    if(max_depth == 0)
        return 0;

    if(max_depth == 1)
        return 3;

    if(max_depth == 2)
        return 10;

    int *chain = calloc(max_depth, sizeof(int));

    int best = 1 << 30;

    for(i = 0; i < (N+max_depth-1)/max_depth; i++) {
        chain[0] = i;
        for(j = 0; j < gp[i].Nb; j++) {
            chain[1] = gp[i].b[j];
            int sum = chain[0] + chain[1];
            traverse(gp[i].b[j], 2, max_depth, sum, &best, chain, gp, N, pr, npr);
        }

        if(best < N)
            revise(&gp, &N, best, i);
    }

    free(chain);

    return best;
}

int main(int argc, char **argv) {
    int N = 100000000;
    int *pr, npr;
    primes(N, &pr, &npr);

    int (*comb)[2] = malloc(10*N*sizeof(int [2]));
    int ncombos = 0;

    combos(pr, npr, &comb, &ncombos);

    qsort(comb, ncombos, sizeof(int [2]), cmp);

    uniq(comb, &ncombos);

    comb = realloc(comb, ncombos * sizeof(int [2]));

    group_t *gp = malloc(N * sizeof(group_t));
    group(comb, ncombos, gp, N);

    int chainlen = 5;
    int sum = min_chain_sum(chainlen, gp, N, pr, npr);
    printf("solution for chain len == %d: %d\n", chainlen, sum);

    return 0;
}
