#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct _payload_t {
    void *item;
    _payload_t *next;
    _payload_t *prev;
} payload_t;

typedef struct {
    long item_size;
    long num_items;
    payload_t *head, *tail;
} queue_t;

bool init(int item_size, queue_t *q) {
    q->item_size = item_size;
    q->num_items = 0;
    q->head = NULL;
    q->tail = NULL;

    return true;
}

bool enqueue(void *item, queue_t *q) {
    payload_t *node = malloc(sizeof(payload_t));
    node->item = malloc(q->item_size);
    memcpy(node->item, item, q->item_size);
    node->next = NULL;
    node->prev = q->tail;

    if(NULL == q->tail) {
        if(NULL != q->head)
            return false;

        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
    }

    q->num_items++;

    return true;
}

bool dequeue(void *item, queue_t *q) {
    if(q->head == NULL)
        return false;

    // allow dequeue to null target
    if(item != NULL)
        memcpy(item, q->head->item, q->item_size);

    payload_t *node = q->head;
    q->head = node->next;
    q->head->prev = NULL;

    free(node->item);
    free(node);

    q->num_items--;

    return true;
}

bool isempty(queue_t *q) {
    return q->num_items == 0;
}

bool cleanup(queue_t *q) {
    while(dequeue(NULL, q));

    q->item_size = 0;

    return true;
}

#endif
