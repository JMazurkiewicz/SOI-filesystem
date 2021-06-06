/// @author Jakub Mazurkiewicz

#include "vfs.h"

struct block load_block(FILE* disk) {
    struct block block;
    fread(&block, sizeof(struct block), 1, disk);
    return block;
}

struct inode load_inode(FILE* disk) {
    struct inode inode;
    fread(&inode, sizeof(struct inode), 1, disk);
    return inode;
}

struct super_block load_super_block(FILE* disk) {
    rewind(disk);
    struct super_block sblock;
    fread(&sblock, sizeof(struct super_block), 1, disk);
    return sblock;
}

vint_t calculate_block_index(vint_t block_offset) {
    return (block_offset - HEADER_SIZE) / BLOCK_SIZE;
}

vint_t count_taken_inodes(const struct super_block* sblock) {
    return sblock->inode_count - sblock->free_inode_count;
}

bool validate_super_block(const struct super_block* sblock) {
    return sblock->magic == SBLOCK_MAGIC;
}

vint_t fseek_first_free_block(FILE* disk, const struct super_block* sblock) {
    vint_t free_block_offset = sblock->first_block_offset;
    fseek(disk, free_block_offset, SEEK_SET);

    do {
        struct block block = load_block(disk);
        if(block.next_block_offset == FREE_BLOCK_MARK) {
            break;
        }

        free_block_offset += BLOCK_SIZE;
    } while(true);

    fseek(disk, free_block_offset, SEEK_SET);
    return free_block_offset;
}

vint_t fseek_next_free_block(FILE* disk) {
    fseek(disk, (long)sizeof(struct block), SEEK_CUR);
    vint_t free_block_offset = ftell(disk);
    
    do {
        struct block block = load_block(disk);
        if(block.next_block_offset == FREE_BLOCK_MARK) {
            break;
        }

        free_block_offset += BLOCK_SIZE;
    } while(true);

    fseek(disk, -(long)sizeof(struct block), SEEK_CUR);
    return free_block_offset;
}

vint_t fseek_first_free_inode(FILE* disk, const struct super_block* sblock) {
    vint_t free_inode_offset = sblock->first_inode_offset;
    fseek(disk, free_inode_offset, SEEK_SET);

    do {
        struct inode inode = load_inode(disk);
        if(inode.first_block_offset == FREE_INODE_MARK) {
            break;
        }

        free_inode_offset += sizeof(struct inode);
    } while(true);

    fseek(disk, free_inode_offset, SEEK_SET);
    return free_inode_offset;
}

void write_block(FILE* disk, const struct block* block) {
    fwrite(block, sizeof(struct block), 1, disk);
}

void write_inode(FILE* disk, const struct inode* inode) {
    fwrite(inode, sizeof(struct inode), 1, disk);
}

void write_super_block(FILE* disk, const struct super_block* sblock) {
    rewind(disk);
    fwrite(sblock, sizeof(struct super_block), 1, disk);
}
