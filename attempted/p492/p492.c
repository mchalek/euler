#include <prime.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <pthread.h>

#define X 1000000000l
#define Y 10000000l
#define Z 1000000000000000l
//#define Z 1000l

#define NTHREADS 3
#define WORK_SIZE (((X + Y + 63) / 64) * sizeof(uint64_t))

#define NEXT(a) (6*(a)*(a) + 10*(a) + 3) // == (3a + 3)(2a + 1) + a
                                         // == (6a + 4)(a + 1) - 1

#define LOGFILE "results.log"

typedef struct _tasks {
    long *items;
    long num_items;
    long next_item;
    pthread_mutex_t mutex;
} tasks_t;

long next(tasks_t *tasks) {
    long ret = -1;
    pthread_mutex_lock(&tasks->mutex);
    if(tasks->next_item < tasks->num_items) {
        ret = tasks->items[tasks->next_item];
        tasks->next_item++;
    }
    pthread_mutex_unlock(&tasks->mutex);

    return ret;
}

typedef struct _result {
    long p;
    long Bp;
} result_t;

typedef struct _results {
    result_t *items;
    int num_items;
    pthread_mutex_t mutex;
} results_t;

long sum = 0;

void update(results_t *results, long p, long Bp)
{
    result_t r;
    r.p = p;
    r.Bp = Bp;

    pthread_mutex_lock(&results->mutex);
    FILE *fp = fopen(LOGFILE, "a");
    fprintf(fp, "%ld\t%ld\n", p, Bp);
    fclose(fp);
    sum += Bp;
    pthread_mutex_unlock(&results->mutex);
}

typedef struct _stuff {
    tasks_t *tasks;
    results_t *results;
    uint64_t *work;
} stuff_t;
    

bool check_and_update(long idx, uint64_t *work) {
    uint64_t word = idx / 64;
    uint64_t bit = 1ul << (idx % 64);

    bool ret = work[word] & bit;

    work[word] |= bit;

    return ret;
}

long B(long p, uint64_t *work) {
    memset(work, 0, WORK_SIZE);

    long a = 1;
    long i = 0;

    while(!check_and_update(a, work)) {
        i++;
        a = NEXT(a) % p;
    }

    long cycle_len = i;
    long cycle_start = a;

    long z = Z;
    a = 1;
    while(a != cycle_start) {
        cycle_len--;
        z--;
        a = NEXT(a) % p;
    }

    printf("cycle len for p == %ld is %ld (repeats at %ld)\n", p, cycle_len, cycle_start);

    z %= cycle_len;

    a = cycle_start;
    for(i = 0; i < z - 1; i++) {
        a = NEXT(a) % p;
    }

    printf("a_%ld for p == %ld is %ld\n", Z, p, a);
    return a;
}

void *worker(void *vstuff)
{
    stuff_t *stuff = (stuff_t *) vstuff;
    tasks_t *tasks = stuff->tasks;
    results_t *results = stuff->results;
    uint64_t *work = stuff->work;

    long p;
    while((p = next(tasks)) != -1) {
        long Bp = B(p, work);

        update(results, p, Bp);
    }

    return NULL;
}

int main()
{
    long *p, np;
    primes(100000, &p, &np);

    long i;

    FILE *fp = fopen(LOGFILE, "r");
    uint64_t *hits = calloc((X + Y + 63) / 64, sizeof(uint64_t));
    if(fp) {
        printf("logfile found.\n");
        char buf[1024];
        while(NULL != fgets(buf, sizeof(buf), fp)) {
            char *tok;

            tok = strtok(buf, "\t");
            long p = strtol(tok, NULL, 10);
            
            tok = strtok(NULL, "\t");
            long Bp = strtol(tok, NULL, 10);
            sum += Bp;

            check_and_update(p, hits);
        }
        fclose(fp);
        fp = NULL;
    } else
        printf("no logfile found\n");

    long nt = 0;
    for(i = X; i <= X + Y; i++) {
        if(isprime(i, p, np))
            nt++;
    }

    tasks_t tasks;
    tasks.num_items = 0;
    tasks.items = malloc(nt*sizeof(long));
    for(i = X; i <= X + Y; i++) {
        if(isprime(i, p, np) && !check_and_update(i, hits))
            tasks.items[tasks.num_items++] = i;
    }
    free(hits);

    printf("%ld / %ld tasks remaining, queued.\n", tasks.num_items, nt);

    tasks.next_item = 0;
    pthread_mutex_init(&tasks.mutex, NULL);

    results_t results;
    pthread_mutex_init(&results.mutex, NULL);

    pthread_t threads[NTHREADS];

    for(i = 0; i < NTHREADS; i++) {
        stuff_t *stuff = malloc(sizeof(stuff_t));

        stuff->tasks = &tasks;
        stuff->results = &results;
        stuff->work = malloc(WORK_SIZE);

        pthread_create(threads + i, NULL, worker, stuff);
    }

    for(i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("sum: %ld\n", sum);

    return 0;
}
