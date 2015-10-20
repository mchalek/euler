#include <stdio.h>
#include <stdlib.h>

// express a power of 2 this way, we have all combinations of:
// 100000000 == 2^N
// 020000000
// 012000000
// 011200000
// ...
// 011111120
// 011111112
//
// so there are N places to put a 2, and 1 place to put the 1
// note that after the 2, we always have all-zeros.  We should be able
// to do some kind of dynamic programming thing whereby we keep track of
// the possible values of each exponent as we add in more powers, going
// from high to low.

//int base2[] = {83, 78, 74, 72, 71, 68, 66, 64, 60, 58, 57, 52, 50, 40, 38, 35, 30, 27, 25};
//int base2[] = {3,1}; // 10
//int base2[] = {6, 5, 2}; // 100
//int base2[] = {16, 15, 10, 9, 7, 5}; // 100000
//int base2[] = {26, 24, 23, 22, 21, 20, 18, 16, 15, 14, 13, 8}; // 10^8
//int base2[] = {39, 38, 37, 35, 31, 30, 28, 26, 23, 21, 18, 16, 12};
//int base2[] = {49, 48, 47, 43, 42, 40, 38, 37, 36, 35, 34, 33, 31, 29, 26, 23, 22, 18, 17, 15}; // 10^15
//int base2[] = {59, 58, 56, 55, 54, 53, 47, 45, 44, 42, 41, 39, 37, 36, 33, 32, 31, 29, 26, 25, 24, 22, 21, 18}; // 10^18
//int base2[] = {63, 59, 57, 55, 54, 50, 49, 48, 45, 41, 40, 34, 31, 27, 24, 23, 22, 21, 19}; // 10^19
//int base2[] = {66, 64, 62, 61, 59, 57, 56, 55, 54, 50, 49, 48, 46, 44, 43, 42, 41, 37, 35, 34, 32, 30, 29, 25, 24, 20}; // 10^20
//int base2[] = {33, 30, 28, 26, 19, 17, 16, 15, 14, 13, 10}; // 10000000000
//int base2[] = {83, 74, 71, 66, 60, 57, 50, 38, 30}; // testing
//int base2[] = {78, 72, 68, 64, 58, 52, 40, 35, 27, 25}; // 10^25
//int base2[] = {85, 72};
//int base2[] = {3, 1};
//int base2[] = {83, 78, 74, 72, 71, 68, 66, 64, 60, 58, 57, 52, 50, 40, 38, 35, 30, 27, 25}; // 10^25

/*
8 + 2:

1 0 1 0 ==
1 0 0 0 + 0 0 1 0
0 2 0 0 + 0 0 1 0
0 1 2 0 + 0 0 0 2
0 1 1 2 + 0 0 1 0 
0 1 1 2 + 0 0 0 2 XXX
0 2 0 0 + 0 0 0 2
1 0 0 0 + 0 0 0 2
*/

int main(int argc, char *argv[])
{
    if(argc < 2) {
        printf("SYNTAX: %s power0 power1 ...\n", argv[0]);
        exit(0);
    }

    int num_powers = argc-1;
    int *base2 = malloc(num_powers*sizeof(int));
    int i;
    for(i = 0; i < num_powers; i++) {
        base2[i] = atoi(argv[1+i]);
    }

    long *intermediates = calloc(num_powers, sizeof(long));

    intermediates[num_powers-1] = base2[num_powers-1] + 1;
    for(i = num_powers-2; i >= 0; i--) {
        int j;
        
        intermediates[i] += intermediates[i+1]*(base2[i]-base2[i+1]);
        for(j = i+1; j < num_powers-1; j++) {
            intermediates[i] += intermediates[j+1]*(base2[j]-base2[j+1]-1);
        }
        intermediates[i] += base2[num_powers-1];
    }

    printf("result: %ld\n", intermediates[0]);
}
