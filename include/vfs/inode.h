/// @author Jakub Mazurkiewicz

#ifndef VFS_INODE_H
#define VFS_INODE_H

#include "def.h"

struct inode {
    char file_name[32];
    vint_t file_size;
    vint_t first_block_offset;
};

#endif
