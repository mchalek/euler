#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int p[] = {181, 179, 173, 167, 163, 157, 151, 149, 139, 137, 131, 127, 113, 
    109, 107, 103, 101, 97, 89, 83, 79, 73, 71, 67, 61, 59, 53, 47, 43, 41,
    37, 31, 29, 23, 19, 17, 13, 11, 7, 5, 3, 2};

#define NPRI 42

struct arrpair {
    double sum;
    int p;
};

void sumList(const double logp[], int p, double sum, int zero, int n, int nstop, int *k, struct arrpair list[])
{
    if(n > nstop) {
        list[*k].p = p;
        list[(*k)++].sum = sum;
        return;
    }

    sumList(logp, p | (1l << (n-zero)), sum + logp[n], zero, n + 1, nstop, k, list);
    sumList(logp, p, sum, zero, n + 1, nstop, k, list);
    return;
}

int pairCmp(const void *A, const void *B)
{
    /* They will never be equal */
    return (((struct arrpair *) A) -> sum < ((struct arrpair *) B) -> sum) ? -1 : 1;
}

void findMax(int k, struct arrpair *list, double limit, struct arrpair *res)
{
    int i0 = 0, i1 = k, ix;

    if(limit > list[k-1].sum) {
        *res = list[k-1];
        return;
    }

    while(i0 != i1) {
        ix = (i0 + i1) / 2;
        
        if(i0 + 1 == i1)
            break;

        if(list[ix].sum > limit)
            i1 = ix;

        if(list[ix].sum < limit)
            i0 = ix;
    }

    *res = list[ix];
    return;
}

int main(void)
{
    double logp[42];
    struct arrpair *listlow, *listhi, maxPair;
    double maxsum = 0, sopt;
    int klo = 0, khi = 0;
    int i, phi, plo;
    unsigned long int ans = 1;

    for(i = 0; i < NPRI; i++) {
        logp[i] = log10(p[i]);
        maxsum += logp[i];
    }
    maxsum /= 2;

    listlow = (struct arrpair *) malloc(sizeof(struct arrpair) * (1l << 21));
    listhi = (struct arrpair *) malloc(sizeof(struct arrpair) * (1l << 21));

    printf("Generating tables...");
    sumList(logp, 0, 0.0, 0, 0, NPRI/2-1, &khi, listhi);
    sumList(logp, 0, 0.0, NPRI/2, NPRI/2, NPRI-1, &klo, listlow);
    printf("Done.\nSorting...");
    fflush(stdout);
    qsort(listhi, khi, sizeof(struct arrpair), pairCmp);
    qsort(listlow, klo, sizeof(struct arrpair), pairCmp);
    printf("Done.\nSearching...");
    fflush(stdout);


    sopt = 0.0;

    for(i = 0; i < khi; i++) {
        if(maxsum > listhi[i].sum)
            findMax(klo, listlow, maxsum - listhi[i].sum, &maxPair);
        else
            maxPair.sum = 0;

        if(maxPair.sum + listhi[i].sum > sopt &&
                maxPair.sum + listhi[i].sum < maxsum) {
            sopt = maxPair.sum + listhi[i].sum;
            plo = maxPair.p;
            phi = listhi[i].p;
        }
    }

    printf("Done.\nresult:\n\t");
    for(i = 0; i < 21; i++)
        if(phi & (1l << i)) {
            printf("%d * ", p[i]);
            ans *= p[i];
            ans %= 10000000000000000;
        }

    for(i = 0; i < 21; i++)
        if(plo & (1l << i)) {
            printf("%d * ", p[i+21]);
            ans *= p[i+21];
            ans %= 10000000000000000;
        }

    printf("== %llu\n", ans);

    return 0;
}

