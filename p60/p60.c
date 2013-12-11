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

void uniq(int (*x)[2], int *nx, int *na) {
    int ny = 0;
    int ac = 0, bc = 0;
    int i;

    for(i = 0; i < *nx; i++) {
        int a = x[i][0];
        int b = x[i][1];

        if(ac != a)
            (*na)++;

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
    int a;
    int *b;
    int Nb;
} group_t;

void group(int (*comb)[2], int ncombos, group_t *g) {
    int i = 0;
    int ng = 0;

    while(i < ncombos) {
        int a = comb[i][0];
        int j = i;
        while((j < ncombos) ? comb[j][0] == a : 0)
            j++;

        int Nb = j-i;
        g[ng].a = a;
        g[ng].Nb = Nb;
        g[ng].b = malloc(Nb*sizeof(int));
        int k;
        for(k = 0; k < Nb; k++)
            g[ng].b[k] = comb[i+k][1];

        ng++;
        i = j;
        //printf("found %d combos paired with %d\n", Nb, a);
    }
}

int main(int argc, char **argv) {
    int N = 10000000;
    int *pr, npr;
    primes(N, &pr, &npr);

    int (*comb)[2] = malloc(10*N*sizeof(int [2]));
    int ncombos = 0;

    combos(pr, npr, &comb, &ncombos);

    qsort(comb, ncombos, sizeof(int [2]), cmp);

    int nhead = 0;
    uniq(comb, &ncombos, &nhead);

    comb = realloc(comb, ncombos * sizeof(int [2]));

    printf("%d unique combos.\n", ncombos);

    int i;
    for(i = 0; i < ncombos; i++)
        printf("%d/%d\n", comb[i][0], comb[i][1]);

    group_t *gp = malloc(nhead * sizeof(group_t));
    group(comb, ncombos, gp);

    return 0;
}
