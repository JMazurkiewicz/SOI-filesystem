/// @author Jakub Mazurkiewicz

#ifndef VFS_H
#define VFS_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t vint_t;

#define SCNVINT SCNu32
#define PRIVINT PRIu32

#define BLOCK_SIZE ((vint_t)4096)
#define SBLOCK_MAGIC ((vint_t)0x73766673)
#define MAX_INODE_COUNT ((vint_t)32)
#define HEADER_SIZE ((vint_t)(sizeof(struct super_block) + MAX_INODE_COUNT * sizeof(struct inode)))
#define MIN_DISK_SIZE ((vint_t)(HEADER_SIZE + BLOCK_SIZE * MAX_INODE_COUNT))
#define MAX_BLOCK_DATA ((vint_t)(BLOCK_SIZE - sizeof(vint_t)))
#define END_BLOCK_MARK ((vint_t)(-1))
#define FREE_BLOCK_MARK ((vint_t)0)
#define FREE_INODE_MARK ((vint_t)0)

struct block {
    unsigned char data[MAX_BLOCK_DATA];
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

struct block load_block(FILE* disk);
struct inode load_inode(FILE* disk);
struct super_block load_super_block(FILE* disk);

bool validate_super_block(const struct super_block* sblock);
vint_t count_taken_inodes(const struct super_block* sblock);

vint_t fseek_first_free_block(FILE* disk, const struct super_block* sblock);
vint_t fseek_next_free_block(FILE* disk);
vint_t fseek_first_free_inode(FILE* disk, const struct super_block* sblock);

void write_block(FILE* disk, const struct block* block);
void write_inode(FILE* disk, const struct inode* inode);
void write_super_block(FILE* disk, const struct super_block* sblock);

int vfs_new(const char* disk_name, vint_t size);
int vfs_copy_from_native_to_virtual(FILE* disk, FILE* file, const char* file_name);
int vfs_copy_from_virtual_to_native(FILE* disk, const char* file_name);
int vfs_print(FILE* disk);
int vfs_stats(FILE* disk);
int vfs_remove(FILE* disk, const char* file_name);
int vfs_delete(const char* disk_name);

#endif
