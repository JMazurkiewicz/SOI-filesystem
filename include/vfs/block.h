#ifndef VFS_BLOCK_H
#define VFS_BLOCK_H

#include "def.h"

struct block {
    unsigned char data[BLOCK_SIZE - sizeof(vint_t)];
    vint_t next_block;
};

#endif