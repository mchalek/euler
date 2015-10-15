#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _stack_payload_t {
    void *item;
    struct _stack_payload_t *next;
} stack_payload_t;

typedef struct {
    long item_size;
    long num_items;
    stack_payload_t *items;
} stack_t;

static bool stack_init(int item_size, stack_t *st) {
    st->item_size = item_size;
    st->num_items = 0;
    st->items = NULL;

    return true;
}

static bool push(void *item, stack_t *st) {
    stack_payload_t *node = malloc(sizeof(stack_payload_t));
    node->item = malloc(st->item_size);
    memcpy(node->item, item, st->item_size);

    node->next = st->items;
    st->items = node;

    st->num_items++;

    return true;
}

static bool pop(void *item, stack_t *st) {
    if(st->items == NULL) {
        return false;
    }

    // allow pop to null target
    if(item != NULL)
        memcpy(item, st->items->item, st->item_size);

    stack_payload_t *node = st->items;
    
    st->items = st->items->next;

    free(node->item);
    free(node);

    st->num_items--;

    return true;
}

static bool stack_isempty(stack_t *st) {
    return st->num_items == 0;
}

static bool stack_cleanup(stack_t *st) {
    while(pop(NULL, st));

    st->item_size = 0;

    return true;
}

#endif
