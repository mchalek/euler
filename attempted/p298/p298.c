#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _state {
    long score[50];
} state_t;

static inline void unpack(int n, int state[5]) {
    int i = 0;
    for(i = 0; i < 5; i++) {
        state[4-i] = n % 11;
        n /= 11;
    }
}

static inline int pack(int state[5]) {
    int ret = 0;
    int i;

    for(i = 0; i < 5; i++) {
        ret *= 11;
        ret += state[i];
    }

    return ret;
}

bool is_present(int draw, int mem[], int *pos) {
    int i;
    for(i = 0; i < 5; i++)
        if(mem[i] == draw) {
            if(pos)
                *pos = i;
            return true;
        }

    return false;
}

bool update_robin(int draw, int mem_0[], int mem_1[])
{
    bool hit = is_present(draw, mem_0, NULL);

    if(hit) {
        // just copy the memory over and return
        memcpy(mem_1, mem_0, 5*sizeof(int));
        return true;
    } else {
        memcpy(mem_1, mem_0, 4*sizeof(int));
        mem_1[4] = draw;
        return false;
    }
}

bool update_larry(int draw, int mem_0[], int mem_1[])
{
    int hit_pos;
    bool hit = is_present(draw, mem_0, &hit_pos);

    if(hit) {
        // bubble the recent hit to the top of the memory
        memcpy(mem_1, mem_0, hit_pos*sizeof(int));
        memcpy(mem_1 + hit_pos, mem_0 + hit_pos + 1, (5 - hit_pos - 1)*sizeof(int));
        mem_1[4] = draw;
        return true;
    } else {
        memcpy(mem_1, mem_0, 4*sizeof(int));
        mem_1[4] = draw;
        return false;
    }
}

int main(void)
{
    state_t *larry = calloc(161051, sizeof(state_t)); // 11^5 possible states, including empty-mem states
    state_t *robin = calloc(161051, sizeof(state_t));

    // both start with empty memories and score of 0
    larry[0].score[0] = 1;
    robin[0].score[0] = 1;

    int draw;
    for(draw = 0; draw < 50; draw++) {
        printf("doing draw %d\n", draw);
        state_t *larry_new = calloc(161051, sizeof(state_t)); // 11^5 possible states, including empty-mem states
        state_t *robin_new = calloc(161051, sizeof(state_t));

        int prev_state;
        for(prev_state = 0; prev_state < 161051; prev_state++) {
            // iterate over previous memory states
            int extracted[5];
            unpack(prev_state, extracted);
            
            int n;
            for(n = 1; n <= 10; n++) { // iterate over possible values
                int updated[5];
                int score = update_larry(n, extracted, updated);
                int updated_index = pack(updated);

                int i;
                for(i = 0; i + score < 50; i++) { 
                    larry_new[updated_index].score[i+score] += larry[prev_state].score[i];
                }

                score = update_robin(n, extracted, updated);
                updated_index = pack(updated);

                for(i = 0; i + score < 50; i++) {
                    robin_new[updated_index].score[i + score] += robin[prev_state].score[i];
                }
            }
        }

        state_t *tmp = larry;
        larry = larry_new;
        free(tmp);

        tmp = robin;
        robin = robin_new;
        free(tmp);
    }



    return 0;
}
