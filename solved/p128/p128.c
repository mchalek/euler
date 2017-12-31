#include <miller_rabin.h>
#include <stdio.h>

#define TILE_TO_FIND 2000

// SOLUTION METHOD
// Through various arguments you can demonstrate that for any hexagonal ring r
// (centered at tile 1, such that ring 1 is tiles 2..7, ring 2 is 8..19, ...)
// there are only two tiles in the ring that can possibly satisfy PD(n) == 3:
//   - the top-most tile
//   - the tile to the right of the top-most tile (i.e the tile with the maximum
//    value n in the ring)
// Therefore it just comes down to checking those two tiles for each ring.
//
// You can derive certain conditions:
//  - For the top-most tile to have PD(n) == 3, then all of { 6r - 1, 6r + 1, and 12 r + 5 } must be prime
//  - For the other candidate to have PD(n) == 3, then all of { 6r - 1, 6r + 5, and 12r - 7 } must be prime.
//
// So now it's just a simple matter of looping over r and checking these values.

int main() {
    long r = 0l;
    long solution = 0;
    int solution_count = 0;

    while(1) {
        r++;
        if(!mr_isprime(6*r - 1)) {
            continue;
        }

        if(mr_isprime(6*r + 1) && mr_isprime(12*r + 5)) {
            solution_count++;
            solution = 2 + 3*r*(r-1);
            printf("[%4d] PD(%ld) == 3 <corner>\n", solution_count, solution);
            if(solution_count == TILE_TO_FIND) {
                break;
            }
        }

        if(r < 1) {
            continue;
        }

        if(mr_isprime(6*r + 5) && mr_isprime(12*r - 7)) {
            solution_count++;
            solution = 1 + 3*r*(r+1);
            printf("[%4d] PD(%ld) == 3 <edge>\n", solution_count, solution);
            if(solution_count == TILE_TO_FIND) {
                break;
            }
        }
    }
}
