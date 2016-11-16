/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 * See COPYRIGHT in top-level directory.
 */

#ifndef _ZM_HMCS_H
#define _ZM_HMCS_H
#include "lock/zm_lock_types.h"

int zm_hmcs_init(zm_hmcs_t * handle);
int zm_hmcs_acquire(zm_hmcs_t *L);
int zm_hmcs_release(zm_hmcs_t *L);

#endif /* _ZM_HMCS_H */