/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <string.h>

static void vfs_free_blocks(FILE* disk);

int vfs_remove(FILE* disk, const char* file_name) {
    struct super_block sblock = load_super_block(disk);
    if(!validate_super_block(&sblock)) {
        return -1;
    }

    fseek(disk, sblock.first_inode_offset, SEEK_SET);

    for(vint_t i = 0; i < sblock.inode_count; ++i) {
        struct inode inode = load_inode(disk);
        if(strcmp(inode.file_name, file_name) == 0) {
            const vint_t first_block_offset = inode.first_block_offset;

            fseek(disk, -(long)sizeof(struct inode), SEEK_CUR);
            const struct inode empty_inode;
            fwrite(&empty_inode, sizeof(struct inode), 1, disk);

            fseek(disk, first_block_offset, SEEK_SET);
            vfs_free_blocks(disk);
            return 0;
        }
    }

    return -1;
}

void vfs_free_blocks(FILE* disk) {
    do {
        const struct block current_block = load_block(disk);
        const vint_t next_block_offset = current_block.next_block_offset;

        fseek(disk, -(long)BLOCK_SIZE, SEEK_CUR);
        const struct block empty_block = {};
        fwrite(&empty_block, BLOCK_SIZE, 1, disk);

        if(next_block_offset != END_BLOCK_MARK) {
            fseek(disk, next_block_offset, SEEK_SET);
        }
    } while(true);
}