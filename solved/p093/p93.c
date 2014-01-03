#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// code has a known error, doesn't include fractional intermediates.  Still
// finds correct answer (it asserts a tie between 1256 and 1258)

int *pairvalues = NULL;
char *values = NULL;
int *pairs = NULL;
int npair = 0;

int count(int digs[4], char used, int value) {
    int ret = 0;
    if(used == 0x3 || used == 0x5 || used == 0x9 || 
            used == 0x6 || used == 0xa || used == 0xc) {
        int pairvalue = (value << 4) | used;
        if(!pairvalues[pairvalue]) {
            pairs[npair++] = pairvalue;
        }
    }
    if(used == 0xf) {
        int ret = !values[value];
        values[value] = 1;
        return ret;
    }

    int dig;
    for(dig = 0; dig < 4; dig++) {
        if(1 & (used >> dig))
            continue;
    
        char new_used = used | (1 << dig);
    
        if(used) {
            int plus = value + digs[dig];
            int times = value * digs[dig];
            int minus = value - digs[dig];
            int div = (value % digs[dig]) ? -1 : (value / digs[dig]);
            ret += count(digs, new_used, plus);
            ret += count(digs, new_used, times);
        
            if(minus > 0)
                ret += count(digs, new_used, minus);

            if(div > 0)
                ret += count(digs, new_used, div);
        } else {
            ret += count(digs, new_used, digs[dig]);
        }
    }

    return ret;
}

int do_pairs() {
    int i, j;
    for(i = 0; i < npair; i++) {
        char usedi = pairs[i] & 0xf;
        int valuei = pairs[i] >> 4;
        for(j = 0; j < npair; j++) {
            char usedj = pairs[j] & 0xf;
            int valuej = pairs[j] >> 4;

            if((usedj | usedi) == 0xf) {
                int plus = valuei + valuej;
                int times = valuei * valuej;
                int minus = valuei - valuej;
                int div = (valuei % valuej) ? -1 : (valuei / valuej);

                values[plus] = 1;
                values[times] = 1;
                if(minus > 0)
                    values[minus] = 1;
                if(div > 0)
                    values[div] = 1;
            }
        }
    }

    return 0;
}

char (*digs)[4] = NULL;
int nperms = 0;

void perms(char perm[4], int depth) {
    if(depth == 4) {
        memcpy(digs[nperms], perm, 4*sizeof(char));
        nperms++;
        return;
    }
    int i, min_i, max_i;
    if(depth == 0) {
        min_i = 1;
    } else {
        min_i = perm[depth-1]+1;
    }
    max_i = 7+depth;

    for(i = min_i; i < max_i; i++) {
        perm[depth] = i;
        perms(perm, depth+1);
    }
}

void make_perms() {
    char perm[4];
    perms(perm, 0);
}

int num_consec(void) {
    int i = 0;
    while(values[i+1])
        i++;

    return i;
}

int main(void) {
    digs = malloc(5040*sizeof(char [4]));
    values = calloc(100000, sizeof(char)); // there's no way we'll hit 100k
    pairvalues = calloc(100000, sizeof(int));
    pairs = malloc(100000*sizeof(int));

    make_perms();

    int perm[4];
    int i;
    for(i = 0; i < nperms; i++) {
        int j;
        for(j = 0; j < 4; j++)
            perm[j] = digs[i][j];

        memset(values, 0, 100000*sizeof(char));
        memset(pairvalues, 0, 100000*sizeof(int));
        npair = 0;
        count(perm, 0, 0);
        do_pairs();
        int consec = num_consec();

        printf("%d for perm %d %d %d %d\n", consec, perm[0], perm[1],
                perm[2], perm[3]);
    }

    return 0;
}
