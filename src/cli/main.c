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

#include <stdlib.h>

#include "eopkg.h"
#include "util.h"

int main(__eopkg_unused__ int argc, __eopkg_unused__ char **argv)
{
        EopkgContext *c = NULL;

        c = eopkg_open();
        eopkg_close(c);

        return EXIT_SUCCESS;
}
