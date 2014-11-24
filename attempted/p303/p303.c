#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 10000

void doit(size_t ntest, uint64_t *test, uint64_t *f) {
    uint64_t i, k;
    uint64_t min, *next;
    uint64_t nnext = 0;

    uint64_t *prev_test;
    
    if(test) {
        min = 0;
        next = malloc(3*ntest*sizeof(uint64_t));
        prev_test = test;
    } else {
        min = 1;
        next = malloc(2*sizeof(uint64_t));
        prev_test = calloc(1, sizeof(uint64_t));
        ntest = 1;
    }

    for(k = 0; k < ntest; k++) {
        uint64_t cur_test = prev_test[k];

        for(i = min; i < 3; i++) {
            uint64_t new_test = cur_test * 10ul + i;
            if(new_test < cur_test) {
                fprintf(stderr, "OVERFLOW\n");
                exit(0);
            }
            next[nnext++] = new_test;

            //printf("testing %ld\n", new_test);


            int64_t j;
            for(j = 1; j <= N; j++) {
                if(f[j] && f[j] < new_test) {
                    continue;
                }

                if(!(new_test % j)) {
                    //printf("f %ld hit for j == %ld\n", new_test, j);
                    f[j] = new_test;
                }
            }
        }
    }

    free(prev_test);

    int64_t complete_count = 0;
    for(k = 1; k <= N; k++) {
        if(f[k])
            complete_count++;
    }
    printf("complete count is %ld\n", complete_count);

    if(complete_count == N)
        return;

    doit(nnext, next, f);

    return;
}

int main(void)
{
    uint64_t *f = calloc(N+1, sizeof(uint64_t));
    uint64_t result = 0ul;

    uint64_t i;
    bool stop = false;

    while(!stop) {
        doit(0ul, NULL, f);

        stop = true;
        for(i = 1; i <= N && stop; i++) {
            stop &= (f[i] > 0);
        } 
    }

    for(i = 1; i <= N; i++) {
        result += f[i] / i;
    }

    printf("result: %ld\n", result);

    return 0;
}
