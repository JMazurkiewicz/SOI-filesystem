/// @author Jakub Mazurkiewicz

#ifndef VFS_H
#define VFS_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t vint_t;
#define SCNVINT SCNu32

#define BLOCK_SIZE ((vint_t)4096)

struct block {
    unsigned char data[BLOCK_SIZE - sizeof(vint_t)];
    vint_t next_block;
};

struct inode {
    char file_name[32];
    vint_t file_size;
    vint_t first_block_offset;
};

#define SBLOCK_MAGIC ((vint_t)0x73766673)

struct super_block {
    vint_t magic;

    vint_t disk_size;
    vint_t file_count;

    vint_t block_count;
    vint_t free_block_count;

    vint_t inode_count;
    vint_t free_inode_count;
};

struct super_block scan_super_block(FILE* disk);
void print_super_block(FILE* disk, struct super_block* sblock);

int vfs_new(const char* disk_name, vint_t size);
int vfs_copy_from_native_to_virtual(FILE* disk, FILE* file);
int vfs_copy_from_virtual_to_native(FILE* disk, const char* file_name);

void vfs_delete(const char* disk_name);

void vfs_print(FILE* disk);
void vfs_remove(const char* disk_name, const char* file_name);

#endif
