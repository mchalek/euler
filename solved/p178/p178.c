#include <stdio.h>
#include <stdlib.h>

// dynamic programming, essentially, keeping track of 4 types of numbers:
//  - those that contain neither 0 nor 9
//  - those that contain 9 but not 0
//  - those that contain 0 but not 9
//  - those that contain both 9 and 0
//
//  Note that due to these being "step numbers", the final condition
//  is necessary and sufficient for being pandigital

void initialize(long h0[], long h9[], long hn[], long pd[]) {
    hn[1] = 1;
    hn[2] = 1;
    hn[3] = 1;
    hn[4] = 1;
    hn[5] = 1;
    hn[6] = 1;
    hn[7] = 1;
    hn[8] = 1;
    h9[9] = 1;
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("SYNTAX: %s ndig [ndig == 40 solves problem]\n", argv[0]);
        exit(0);
    }
    int max_length = atoi(argv[1]);

    long *hit_0 = calloc(10, sizeof(long));
    long *hit_9 = calloc(10, sizeof(long));
    long *hit_nil = calloc(10, sizeof(long));
    long *pandigital = calloc(10, sizeof(long));

    initialize(hit_0, hit_9, hit_nil, pandigital);

    int current_length;
    long result = 0;
    for(current_length = 1; current_length < max_length; current_length++) {
        int j;
        long *new_hit_0 = calloc(10, sizeof(long));
        long *new_hit_9 = calloc(10, sizeof(long));
        long *new_hit_nil = calloc(10, sizeof(long));
        long *new_pandigital = calloc(10, sizeof(long));

        // first update hit_nil -> X
        new_hit_0[0] += hit_nil[1];
        new_hit_nil[2] += hit_nil[1];
        for(j = 2; j < 8; j++) {
           new_hit_nil[j-1] += hit_nil[j]; 
           new_hit_nil[j+1] += hit_nil[j]; 
        }
        new_hit_9[9] += hit_nil[8];
        new_hit_nil[7] += hit_nil[8];

        // now update hit_0 -> X
        new_hit_0[1] += hit_0[0];
        for(j = 1; j < 8; j++) {
            new_hit_0[j-1] += hit_0[j];
            new_hit_0[j+1] += hit_0[j];
        }
        new_pandigital[9] += hit_0[8];
        new_hit_0[7] += hit_0[8];
        
        // now hit_9 -> X
        new_pandigital[0] += hit_9[1];
        new_hit_9[2] += hit_9[1];
        for(j = 2; j < 9; j++) {
            new_hit_9[j-1] += hit_9[j];
            new_hit_9[j+1] += hit_9[j];
        }
        new_hit_9[8] += hit_9[9];

        // finally update pandigital -> pandigital
        new_pandigital[1] += pandigital[0];
        for(j = 1; j < 9; j++) {
            new_pandigital[j-1] += pandigital[j];
            new_pandigital[j+1] += pandigital[j];
        }
        new_pandigital[8] += pandigital[9];

        for(j = 0; j < 10; j++) {
            result += new_pandigital[j];
        }

        free(hit_0);
        free(hit_9);
        free(hit_nil);
        free(pandigital);

        hit_0 = new_hit_0;
        hit_9 = new_hit_9;
        hit_nil = new_hit_nil;
        pandigital = new_pandigital;
    }

    printf("result: %ld\n", result);

    return 0;
}
