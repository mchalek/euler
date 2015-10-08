#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <kmbits.h>

#define NUM_PIECES 40

static inline int count_pieces(uint64_t config) {
    int result = 0;
    while(config) {
        result++;
        config >>= _trailz(config);
        config >>= _trailz(~config);
    }

    return result;
}

void random_shuffle(int items[]) {
    int i;
    for(i = 0; i < NUM_PIECES-1; i++) {
        int ind = i + (rand() % (NUM_PIECES-i));
        int tmp = items[ind];
        items[ind] = items[i];
        items[i] = tmp;
    }
}

int execute() {
    int i;
    int pieces[NUM_PIECES];
    for(i = 0; i < NUM_PIECES; i++)
        pieces[i] = i;

    random_shuffle(pieces);

    uint64_t state = 0;
    int max_count = 0;
    for(i = 0; i < NUM_PIECES; i++) {
        state |= 1ul << pieces[i];
        int count = count_pieces(state);

        if(count > max_count) {
            max_count = count;
        }
    }

    return max_count;
}


int main(void) {
    int i;
    double sum = 0.0;
    int num_trials = 10000000;
    srand(time(NULL));
    for(i = 0; i < num_trials; i++) {
        sum += execute();
    }
    printf("mean by shitty simulation: %.6f\n", sum / num_trials);
    
    return 0;
}
