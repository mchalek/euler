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
// note that after the 2, we always have all-zeros.

/*
To solve, we start from the smallest power (which has p+1 possible
representations) and then continually add bigger powers.  With each addition,
we just have to keep track of the number of ways to include the representation
of the new power alongside the old ones.  This comes down to how many ways
we can insert the terminal 2 in one of the representations of the new power.
Note that there are p_new - p_old ways to place that 2 to the left of the
previously-highest power, all of which accept all valid representations of 
N_old alone.  However once we try to place the 2 for p_new at or beyond
p_old, we have to account for what this does.  If the 2 for p_new is placed
beyond p_old, then we can only recognize one representation of p_old, i.e.
the one with a 1 at p_old.

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
