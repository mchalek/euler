#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kmbits.h>
#include <queue.h>

#define PM_NUM 524287
#define MODULUS 1000000

long k = 0;
long read = 0;
int S[55];

int next_int(void) {
    if(++k < 56) {
        long k3 = (k*k*k) % MODULUS;
        int result = (100003 - 200003*k + 300007*k3) % MODULUS;
        S[read++] = result;
        read %= 55;
        return result;
    } else {
        int read_minus_24 = (read + 55 - 24) % 55;
        int read_minus_55 = read;

        int result = (S[read_minus_24] + S[read_minus_55]) % MODULUS;
        S[read++] = result;
        read %= 55;

        return result;
    }
}

uint64_t next_call() {
    int c0 = next_int();
    int c1 = next_int();

    //printf("call: %8d %8d\n", c0, c1);

    uint64_t result = c1;
    result |= ((uint64_t) c0) << 32;

    return result;
}

typedef struct {
    int num_calls;
    int called[255];
} user_t;

void append_user(int caller, user_t *user)
{
    int prev_count = user->num_calls++;
    user->called[prev_count] = caller;
}

int insert(int caller0, int caller1, user_t *calls) {
    int num_new_users = !calls[caller0].num_calls + !calls[caller1].num_calls;
    append_user(caller0, calls + caller1);
    append_user(caller1, calls + caller0);

    return num_new_users;
}

bool in_pm_net(int caller, uint64_t *is_friend) {
    int word = caller / 64;
    uint64_t bit = 1ul << (caller % 64);

    return is_friend[word] & bit;
}

bool set_if_not(int caller, uint64_t *is_friend) {
    int word = caller / 64;
    uint64_t bit = 1ul << (caller % 64);

    bool state = is_friend[word] & bit;

    is_friend[word] |= bit;

    return state;
}

int count_connected(uint64_t *words) {
    int ret = 0;
    int i;
    int num_words = (MODULUS+63) / 64;

    for(i = 0; i < num_words; i++) {
        ret += _popcnt(words[i]);
    }

    return ret;
}

void propagate(int caller, uint64_t *is_friend, user_t *calls) {
    // do a queue-based BFS
    set_if_not(caller, is_friend);

    queue_t q;
    queue_init(sizeof(int), &q);
    enqueue(&caller, &q);

    int user;
    while(dequeue(&user, &q)) {
        int i;
        for(i = 0; i < calls[user].num_calls; i++) {
            int friend = calls[user].called[i];
            if(!set_if_not(friend, is_friend)) {
                // enqueue any friend who was not previously in PM network
                enqueue(&friend, &q);
            }
        }
    }

    queue_cleanup(&q);
}

int main(void) {
    uint64_t *is_friend = calloc((MODULUS+63) / 64, sizeof(uint64_t));
    set_if_not(PM_NUM, is_friend); // PM is his only friend at first

    user_t *calls = calloc(MODULUS, sizeof(user_t));

    int network_size = 1000000;
    int connected = count_connected(is_friend);
    int num_calls = 0;
    do {
        uint64_t this_call = next_call();
    
        int caller0 = this_call >> 32;
        int caller1 = this_call & 0xffffffff;

        if(caller0 == caller1)
            continue;

        num_calls++;

        insert(caller0, caller1, calls);

        bool c0_in_net = in_pm_net(caller0, is_friend);
        bool c1_in_net = in_pm_net(caller1, is_friend);

        if(!(num_calls % 100000))
            printf("%d / %d connected after %d calls\n", connected, network_size, num_calls);

        if(!(c0_in_net ^ c1_in_net)) 
            continue;

        if(c0_in_net) {
            propagate(caller1, is_friend, calls);
        } else {
            propagate(caller0, is_friend, calls);
        }

        connected = count_connected(is_friend);
    } while(connected < (network_size * 99) / 100);

    printf("99%% coverage after %d calls!\n", num_calls);
    printf("%d connected out of %d users\n", connected, network_size);

    return 0;
}
