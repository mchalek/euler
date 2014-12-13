#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MODULUS 250
#define MAX_N 250250

int cycle_start[MODULUS];
int path_to_cycle[MODULUS];
int cycle_len[MODULUS];

void init()
{
    int i;
    cycle_len[0] = 1;
    path_to_cycle[0] = 0;
    cycle_start[0] = 0;

    cycle_len[1] = 1;
    path_to_cycle[1] = 0;
    cycle_start[1] = 1;

    bool hit[MODULUS];
    int logs[MODULUS];
    for(i = 2; i < MODULUS; i++) {
        memset(hit, 0, sizeof(hit));
        memset(logs, 0, sizeof(logs));

        int j = i;
        int k = 1;
        do {
            logs[j] = k++;
            hit[j] = true;
            j *= i;
            j %= MODULUS;
        } while(!hit[j]);

        cycle_len[i] = k - logs[j];
        path_to_cycle[i] = logs[j] - 1;
        cycle_start[i] = j;
    }
}

int mipow(int a, int b)
{
    // return a^b % m
    int ret = 1;
    int i;
    for(i = 0; i < b; i++) {
        ret *= a;
        ret %= MODULUS;
    }

    return ret;
}

int nn(int n)
{
    int base = n % MODULUS;
    // compute n^n mod MODULUS
    if(n <= path_to_cycle[base]) {
        return mipow(base, n);
    }

    int cycle_remainder = (n - path_to_cycle[base] - 1) % cycle_len[base];

    return mipow(cycle_start[base], 1 + cycle_remainder);
}

int main()
{
    init();
    int i;

    // for debugging the exponentiation method
    /*
    for(i = 0; i < 400; i++) {
        printf("%d^%d == %d mod %d\n", i, i, nn(i), MODULUS);
    }*/

    long ways[MODULUS];
    memset(ways, 0, sizeof(ways));
    
    ways[0] = 1;
    ways[1] = 1;

    for(i = 2; i <= MAX_N; i++) {
        long prev[MODULUS];
        memcpy(prev, ways, sizeof(prev));
    
        int j;
        int item = nn(i);
        for(j = 0; j < MODULUS; j++) {
            int k = (j + item) % MODULUS;
            ways[k] += prev[j];
            ways[k] %= 10000000000000000l;
        }
    }

    printf("result: %ld\n", ways[0] - 1);

    return 0;
}
