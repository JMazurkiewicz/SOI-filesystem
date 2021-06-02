#ifndef VFS_INODE_H
#define VFS_INODE_H

#include "def.h"

struct inode {
    char file_name[32];
    int32_t file_size;
    int32_t file_block;
};

#endif
