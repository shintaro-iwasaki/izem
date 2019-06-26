/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 * See COPYRIGHT in top-level directory.
 */

#ifndef _ZM_IMCSQUEUE_H
#define _ZM_IMCSQUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include "queue/zm_queue_types.h"

int zm_imcsqueue_init(zm_mcsqueue_t *);
int zm_imcsqueue_enqueue(zm_mcsqueue_t* q, void *data);
int zm_imcsqueue_dequeue(zm_mcsqueue_t* q, void **data);

#endif /* _ZM_IMCSQUEUE_H */
