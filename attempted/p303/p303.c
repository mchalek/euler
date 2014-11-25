#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define N 10000

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct _ns {
    int num_solutions;
    int *solutions;
} ns_t;

typedef struct _q q_t;

struct _q {
    int8_t solution[16];
    int ndig;

    q_t *prev;
    q_t *next;
};

void enqueue(q_t **head, q_t **tail, int ndig, int8_t sol[]) {
    q_t *new = malloc(sizeof(q_t));
    new->ndig = ndig;
    memcpy(new->solution, sol, sizeof(new->solution));

    if(*head) {
        (*head)->prev = new;
    }

    new->next = *head;
    new->prev = NULL;

    *head = new;

    if(!(*tail)) {
        *tail = *head;
    }
}

void dequeue(q_t **head, q_t **tail, int *ndig, int8_t sol[]) {
    *ndig = (*tail)->ndig;
    memcpy(sol, (*tail)->solution, sizeof((*tail)->solution));

    if(*head == *tail)
        *head = NULL;

    q_t *del = *tail;
    *tail = (*tail)->prev;

    if(*tail)
        (*tail)->next = NULL;
    
    free(del);
}

ns_t **table;


int test(uint64_t item) {
    while(item) {
        if((item % 10) >= 3)
            return false;

        item /= 10;
    }

    return true;
}

void init_table(void)
{
    // build a table of solutions to:
    // a + b*x == {0, 1, 2} mod 10, where:
    // - a could be somewhat big, ~1000 maybe
    // - b and x are both digits
    table = malloc(10 * sizeof(ns_t *));
    int a, b, x;
    for(a = 0; a < 10; a++) {
        table[a] = calloc(10, sizeof(ns_t));

        for(b = 0; b < 10; b++) {
            table[a][b].solutions = malloc(10*sizeof(int));
            for(x = 0; x < 10; x++) {
                int item = (a + b*x) % 10;
                if(test(item))
                    table[a][b].solutions[table[a][b].num_solutions++] = x;
            }
        }
    }
}

void unpack(uint64_t n, int *ndig, int8_t digits[]) {
    *ndig = 0;

    while(n) {
        digits[(*ndig)++] = n % 10;
        n /= 10;
    }
}

uint64_t pack(int ndig, int8_t digits[]) {
    int i;
    uint64_t result = 0;

    for(i = ndig-1; i >= 0; i--) {
        result *= 10;
        result += digits[i];
    }

    return result;
}

void mul(int n0, int8_t i0[], int n1, int8_t i1[], int8_t i2[])
{
    int tmp[64];
    memset(tmp, 0, sizeof(tmp));
    memset(i2, 0, 64*sizeof(int8_t));
    int i, j; 
    for(i = 0; i < n0; i++) {
        for(j = 0; j < n1; j++) {
            tmp[i + j] += i0[i]*i1[j];
        }
    }

    for(i = 0; i < 63; i++) {
        tmp[i+1] += tmp[i] / 10;
        tmp[i] %= 10;

        i2[i] = tmp[i];
    }
}

int mul_and_test(int n0, int8_t i0[], int8_t n1, int8_t i1[])
{
    int8_t result[64];
    mul(n0, i0, n1, i1, result);

    int i;
    for(i = 0; i < 64; i++)
        if(result[i] > 2)
            return 0;
    
    return 1;
}


uint64_t compute(uint64_t n) {
    int ndig, sdig;
    int8_t digits[10];
    int8_t solution_digits[16];

    unpack(n, &ndig, digits);

    int b = digits[0];
    ns_t *try = table[0] + b;
    int i;
    q_t *head = NULL, *tail = NULL;
    bool hit = false;
    uint64_t min_hit = 0;
    for(i = 0; i < try->num_solutions; i++) {
        memset(solution_digits, 0, sizeof(solution_digits));
        if(try->solutions[i] == 0)
            continue;

        uint64_t sol = try->solutions[i];
        if(test(sol*n)) {
            min_hit = hit ? MIN(min_hit, sol) : sol;
            hit = true;
        } else {
            solution_digits[0] = sol;
            enqueue(&head, &tail, 1, solution_digits);
        }
    }

    // guaranteed to have found smallest solution, if any solution found
    if(hit)
        return min_hit;

    while(head) {
        dequeue(&head, &tail, &sdig, solution_digits);

        int8_t tmp[64];
        mul(sdig, solution_digits, ndig, digits, tmp);
        
        int a = tmp[sdig];

        ns_t *try = table[a % 10] + b;

        for(i = 0; i < try->num_solutions; i++) {
            solution_digits[sdig] = try->solutions[i];

            int good = mul_and_test(sdig+1, solution_digits, ndig, digits);
            uint64_t sol = pack(sdig+1, solution_digits);

            if(good) {
                min_hit = hit ? MIN(min_hit, sol) : sol;
                hit = true;
            } else {
                if(!hit)
                    enqueue(&head, &tail, sdig+1, solution_digits);
            }
        }
    }

    return min_hit;
}

int main(void)
{
    init_table();

    uint64_t n;
    uint64_t result = 0;

    for(n = 1; n <= N; n++) {
        uint64_t x = compute(n);
        printf("%ld * %ld == %ld\n", n, x, n*x);
        result += x;
    }

    printf("solution: %ld\n", result);

    return 0;
}
