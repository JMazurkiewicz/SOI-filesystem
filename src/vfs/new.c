/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <stdlib.h>
#include <string.h>

static const char DISK_EXT[] = ".vd";

static void vfs_form_super_block(FILE* disk, vint_t size);
static void vfs_form_inodes(FILE* disk, vint_t size);
static void vfs_form_blocks(FILE* disk, vint_t block_count);
static void vfs_form_remaining_bytes(FILE* disk, vint_t byte_count);

int vfs_new(const char* disk_name, vint_t size) {
    if(size < MIN_DISK_SIZE) {
        return -1;
    }

    const size_t file_name_length = strlen(disk_name) + sizeof(DISK_EXT);
    char* file_name = malloc(file_name_length);

    strcpy(file_name, disk_name);
    strcat(file_name, DISK_EXT);

    FILE* const disk = fopen(file_name, "wb+");
    if(disk == NULL) {
        return -1;
    }

    vfs_form_super_block(disk, size);

    fclose(disk);
    free(file_name);
    return 0;
}

void vfs_form_super_block(FILE* disk, vint_t size) {
    struct super_block sblock;
    
    sblock.magic = SBLOCK_MAGIC;
    sblock.disk_size = size;
    
    sblock.first_inode_offset = sizeof(struct super_block);
    sblock.inode_count = MAX_INODE_COUNT;
    sblock.free_inode_count = sblock.inode_count;

    const vint_t possible_blocks = (size - HEADER_SIZE) / BLOCK_SIZE;

    sblock.first_block_offset = HEADER_SIZE;
    sblock.block_count = possible_blocks;
    sblock.free_block_count = sblock.block_count;

    write_super_block(disk, &sblock);
    vfs_form_inodes(disk, size);
    vfs_form_blocks(disk, possible_blocks);

    const vint_t remaining_bytes = sblock.disk_size - (HEADER_SIZE + possible_blocks * BLOCK_SIZE);
    vfs_form_remaining_bytes(disk, remaining_bytes);
}

void vfs_form_inodes(FILE* disk, vint_t size) {
    const struct inode empty_inode = {
        .file_name = {'\0'},
        .file_size = 0,
        .first_block_offset = 0
    };

    for(vint_t i = 0; i < MAX_INODE_COUNT; ++i) {
        write_inode(disk, &empty_inode);
    }
}

void vfs_form_blocks(FILE* disk, vint_t block_count) {
    const struct block empty_block = {
        .data = {0},
        .next_block_offset = 0
    };

    for(vint_t i = 0; i < block_count; ++i) {
        write_block(disk, &empty_block);
    }
}

void vfs_form_remaining_bytes(FILE* disk, vint_t byte_count) {
    unsigned char* const bytes = malloc(byte_count);
    memset(bytes, 0, byte_count);
    fwrite(bytes, sizeof(unsigned char), byte_count, disk);
    free(bytes);
}
