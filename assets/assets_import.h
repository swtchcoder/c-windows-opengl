#ifndef ASSETS_IMPORT
#define ASSETS_IMPORT

#include <stdio.h>
#include "assets_meta.h"

void assets_open(void);
void *assets_load(const size_t offset, const size_t size);
void assets_close(void);

#endif