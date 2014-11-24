#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define N 300
#define MAX_A 100000

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

int test(long item) {
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

void unpack(long n, int *ndig, int8_t digits[]) {
    *ndig = 0;

    while(n) {
        digits[(*ndig)++] = n % 10;
        n /= 10;
    }
}

long pack(int ndig, int8_t digits[]) {
    //printf("packing: ");
    int i;
    //for(i = 0; i < ndig; i++)
        //printf("%d ", digits[i]);
    //printf("\n");
    long result = 0;

    for(i = ndig-1; i >= 0; i--) {
        result *= 10;
        result += digits[i];
    }

    //printf("result: %d\n", result);

    return result;
}

long compute(long n) {
    //printf("%ld:\n", n);
    int ndig, sdig;
    int8_t digits[10];
    int8_t solution_digits[16];

    unpack(n, &ndig, digits);

    int b = digits[0];
    ns_t *try = table[0] + b;
    int i;
    q_t *head = NULL, *tail = NULL;
    bool hit = false;
    long min_hit = 0;
    long sol;
    for(i = 0; i < try->num_solutions; i++) {
        memset(solution_digits, 0, sizeof(solution_digits));
        if(try->solutions[i] == 0)
            continue;

        sol = try->solutions[i];
        if(test(sol*n)) {
            min_hit = hit ? MIN(min_hit, sol) : sol;
            hit = true;
        } else {
            solution_digits[0] = sol;
            enqueue(&head, &tail, 1, solution_digits);
        }
    }

    // guaranteed to have found smallest solution
    if(hit)
        return min_hit;

    while(head) {
        dequeue(&head, &tail, &sdig, solution_digits);

        printf("dequeue: %ld\n", pack(sdig, solution_digits));

        int a = 0;
        int j;

        printf("a == ");

        for(j = 0; j < ndig; j++) {
            int k;
            for(k = 0; k < sdig; k++) {
                if(j + k + 1 == sdig) {
                    printf("(%d * %d)/10 + ", digits[j], solution_digits[k]);
                    a += (digits[j]*solution_digits[k]) / 10;
                }
                if(j + k == sdig) {
                    printf("(%d * %d)%10 + ", digits[j], solution_digits[k]);
                    a += (digits[j]*solution_digits[k]) % 10;
                }
            }
        }

        printf("== %ld\n", a);
        
        ns_t *try = table[a % 10] + b;

        for(i = 0; i < try->num_solutions; i++) {
            printf("try %ld / %ld: %ld\n", i+1, try->num_solutions, try->solutions[i]);
            solution_digits[sdig] = try->solutions[i];

            sol = pack(sdig+1, solution_digits);

            printf("product: %ld\n", sol*n);

            if(test(sol*n)) {
                if(n == 89) {
                    printf("found solution %ld => %ld for n == 89 [a == %ld]\n", sol, sol*n, a);
                }
                min_hit = hit ? MIN(min_hit, sol) : sol;
                hit = true;
            } else {
                if(!hit) {
                    printf("enqueue: %ld\n", pack(sdig+1, solution_digits));
                    enqueue(&head, &tail, sdig+1, solution_digits);
                }
            }
        }
    }

    return min_hit;
}

int main(void)
{
    init_table();

    long n;
    long result = 0;

    for(n = 1; n <= N; n++) {
        n = 89;
        long x = compute(n);
        printf("%ld * %ld == %ld\n", n, x, n*x);
        result += x;
        break;
    }

    printf("solution: %ld\n", result);

    return 0;
}
