/// @author Jakub Mazurkiewicz

#include "vfs.h"

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

bool validate_super_block(const struct super_block* sblock) {
    return sblock->magic == SBLOCK_MAGIC;
}

vint_t count_taken_inodes(const struct super_block* sblock) {
    return sblock->inode_count - sblock->free_inode_count;
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
