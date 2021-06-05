/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <string.h>

static vint_t vfs_free_blocks(FILE* disk);

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
            const struct inode empty_inode = {0};
            fwrite(&empty_inode, sizeof(struct inode), 1, disk);

            fseek(disk, first_block_offset, SEEK_SET);
            const vint_t freed_blocks = vfs_free_blocks(disk);

            sblock.free_block_count += freed_blocks;
            ++sblock.free_inode_count;
            write_super_block(disk, &sblock);
            return 0;
        }
    }

    return -1;
}

vint_t vfs_free_blocks(FILE* disk) {
    vint_t freed_block_counter = 0;

    do {
        const struct block current_block = load_block(disk);
        const vint_t next_block_offset = current_block.next_block_offset;

        fseek(disk, -(long)BLOCK_SIZE, SEEK_CUR);
        const struct block empty_block = {0};
        fwrite(&empty_block, BLOCK_SIZE, 1, disk);
        ++freed_block_counter;

        if(next_block_offset != END_BLOCK_MARK) {
            fseek(disk, next_block_offset, SEEK_SET);
        } else {
            break;
        }
    } while(true);

    return freed_block_counter;
}