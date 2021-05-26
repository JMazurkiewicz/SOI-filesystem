/// @author Jakub Mazurkiewicz
#ifndef VFS_SUPER_BLOCK_H
#define VFS_SUPER_BLOCK_H

#include <stdio.h>

#include "def.h"

struct super_block {
    vint_t disk_size;
    vint_t file_count;

    vint_t block_count;
    vint_t free_block_count;

    vint_t inode_count;
    vint_t free_inode_count;
};

struct super_block scan_super_block(FILE* disk);
void print_super_block(FILE* disk, struct super_block* sblock);

#endif