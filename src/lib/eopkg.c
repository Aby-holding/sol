/*
 * This file is part of eopkg.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * eopkg is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdatomic.h>
#include <stdlib.h>

#include "eopkg.h"
#include "util.h"

struct EopkgContext {
        atomic_int ref_count; /**<Current refcount for this handle */
};

EopkgContext *eopkg_open(void)
{
        return NULL;
}

/**
 * Close the library handle
 */
void eopkg_close(__eopkg_unused__ EopkgContext *eopkg)
{
        return;
}
