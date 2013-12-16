#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline long next(long a, long facts[])
{
    long ret = 0;
    while(a) {
        ret += facts[a % 10];
        a /= 10;
    }
    return ret;
}

int main(void)
{
    long facts[10];

    int i;

    facts[0] = 1;
    for(i = 1; i < 10; i++)
        facts[i] = facts[i-1]*i;

    long a;
    long count = 0;
    int hitsize = 3000000;
    char *hit = malloc(hitsize);
    char *len = calloc(hitsize, 1);
    for(a = 1; a < 1000000; a++) { 
        memset(hit, 0, hitsize);
        int nsteps = 0;
        long b = a;
        while(!hit[b] && !len[b]) {
            hit[b] = nsteps;
            nsteps++;
            b = next(b, facts);
            if(b > hitsize) {
                hit = realloc(hit, hitsize*2);
                len = realloc(len, hitsize*2);
                memset(len + hitsize, 0, hitsize);
                hitsize *= 2;

                printf("REALLOC: %ld\n", b);
            }
        } 
        int chainlen = nsteps + len[b];

        long c = a;
        memset(hit, 0, hitsize);
        nsteps = chainlen;
        while(!hit[c] && !len[c]) {
            len[c] = nsteps;
            c = next(c, facts);
            nsteps--;
        }

        if(chainlen == 60) {
            printf("%d: chain len %d terminal %d\n", a, chainlen, b);
            count++;
        }
        if(!(a % 10000))
            printf("checked a == %ld\n", a);
    }
    printf("%ld chains.\n", count);

    return 0;
}
