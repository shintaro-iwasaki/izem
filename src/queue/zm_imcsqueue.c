/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 * See COPYRIGHT in top-level directory.
 */

#include "queue/zm_imcsqueue.h"
#include "lock/zm_imcs.h"

/* a queue-data pair to pass to the apply functions */
struct qdpair {
    zm_mcsqueue_t *q;
    void **data;
};

int zm_imcsqueue_init(zm_mcsqueue_t *q) {
    zm_listnode_t* node = (zm_listnode_t*) malloc(sizeof(zm_listnode_t));
    node->data = NULL;
    node->next = ZM_NULL;
    q->head = (zm_ptr_t)node;
    q->tail = (zm_ptr_t)node;
    zm_imcs_init(&q->L);
    return 0;
}

static inline void apply_enq(void *args) {
    struct qdpair *pair = (struct qdpair *) args;
    zm_mcsqueue_t *q = pair->q;
    void *data = *pair->data;
    zm_listnode_t* node = (zm_listnode_t*) malloc(sizeof(zm_listnode_t));
    node->data = data;
    node->next = ZM_NULL;
    ((zm_listnode_t*)q->tail)->next = (zm_ptr_t)node;
    q->tail = (zm_ptr_t)node;
}

static inline void apply_deq(void *args) {
    struct qdpair *pair = (struct qdpair *) args;
    zm_mcsqueue_t *q = pair->q;
    void **data = pair->data;
    zm_listnode_t* head;
    head = (zm_listnode_t*)q->head;
    *data = NULL;
    if(head->next != ZM_NULL) {
        q->head = head->next;
        *data = ((zm_listnode_t*)q->head)->data;
        free(head);
    }
}

int zm_imcsqueue_enqueue(zm_mcsqueue_t* q, void *data) {
    struct qdpair pair = {q, &data};
    zm_imcs_acquire(q->L);
    apply_enq(&pair);
    zm_imcs_release(q->L);
    return 0;
}

int zm_imcsqueue_dequeue(zm_mcsqueue_t* q, void **data) {
    struct qdpair pair = {q, data};
    zm_imcs_acquire(q->L);
    apply_deq(&pair);
    zm_imcs_release(q->L);
    return *data == NULL ? 0 : 1;
}
