/// @author Jakub Mazurkiewicz

#ifndef VFS_H
#define VFS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t vint_t;

#define SCNVINT SCNu32
#define BLOCK_SIZE ((vint_t)4096)
#define SBLOCK_MAGIC ((vint_t)0x73766673)
#define MAX_INODE_COUNT ((vint_t)32)
#define HEADER_SIZE ((vint_t)(sizeof(struct super_block) + MAX_INODE_COUNT * sizeof(struct inode)))
#define MIN_DISK_SIZE ((vint_t)(HEADER_SIZE + BLOCK_SIZE * MAX_INODE_COUNT))

struct block {
    unsigned char data[BLOCK_SIZE - sizeof(vint_t)];
    vint_t next_block_offset;
};

struct inode {
    char file_name[32];
    vint_t file_size;
    vint_t first_block_offset;
};

struct super_block {
    vint_t magic;
    vint_t disk_size;

    vint_t first_inode_offset;
    vint_t inode_count;
    vint_t free_inode_count;

    vint_t first_block_offset;
    vint_t block_count;
    vint_t free_block_count;
};

struct inode load_inode(FILE* disk);
struct super_block load_super_block(FILE* disk);

bool validate_super_block(const struct super_block* sblock);
vint_t count_taken_inodes(const struct super_block* sblock);

void write_block(FILE* disk, const struct block* block);
void write_inode(FILE* disk, const struct inode* inode);
void write_super_block(FILE* disk, const struct super_block* sblock);

int vfs_new(const char* disk_name, vint_t size);
int vfs_copy_from_native_to_virtual(FILE* disk, FILE* file);
int vfs_copy_from_virtual_to_native(FILE* disk, const char* file_name);
int vfs_print(FILE* disk);
int vfs_stats(FILE* disk);
int vfs_remove(FILE* disk, const char* file_name);
int vfs_delete(const char* disk_name);

#endif
