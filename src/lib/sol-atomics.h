/*
 * This file is part of sol.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * sol is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#pragma once

#include <assert.h>
#include <stdatomic.h>
#include <stdlib.h>

#include "util.h"

/**
 * Valid unref function for an sol atomic
 */
typedef void (*sol_atomic_free)(void *);

/**
 * Base type for atomic reference types
 *
 * Ensure the sol_atomic_t is the first member in the struct to gain
 * "free" atomic refcounts. Always proxy by sol_atomic_init after
 * construction
 */
typedef struct sol_atomic_t {
        atomic_int ref_count; /**<Current ref count */
        sol_atomic_free dtor; /**<Deconstructor when ref count hits 0 */
} sol_atomic_t;

/**
 * Increase the refcount of a given object by one, atomically.
 *
 * @note: @v is assumed to be an sol_atomic_t based struct
 * @returns a reference to the ref'd struct
 */
__sol_inline__ static inline void *sol_atomic_ref(void *v)
{
        sol_atomic_t *t = v;
        if (!t) {
                return NULL;
        }
        int ref_count = atomic_fetch_add(&(t->ref_count), 1);
        assert(ref_count >= 0);
        return t;
}

/**
 * Initialse an atomic reference type to a refcount of 1
 *
 * @param dtor Deconstructor to call when the refcount hits 0
 * @returns A reference to the object
 */
__sol_inline__ static inline void *sol_atomic_init(sol_atomic_t *atom, sol_atomic_free dtor)
{
        assert(atom->dtor == NULL);
        assert(atomic_load(&(atom->ref_count)) < 1);
        atom->dtor = dtor;
        return sol_atomic_ref(atom);
}

/**
 * Decrease the refcount for an object by 1.
 * @note When the refcount hits 0, the deconstructor is called. If this doesn't
 * exist then it is assumed to be a basic type, and @free is called.
 *
 * @returns A reference to the object if the refcount is higher than 0, or NULL
 */
__sol_inline__ static inline void *sol_atomic_unref(void *v)
{
        sol_atomic_t *t = v;
        if (!t) {
                return NULL;
        }
        int ref_count = atomic_fetch_sub(&(t->ref_count), 1);
        assert(ref_count > 0);
        if (ref_count == 1) {
                if (t->dtor) {
                        t->dtor(t);
                } else {
                        free(t);
                }
                return NULL;
        }
        return t;
}
