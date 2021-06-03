/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <string.h>

int vfs_copy_from_native_to_virtual(FILE* disk, FILE* file, const char* file_name) {
    struct super_block sblock = load_super_block(disk);

    if(!validate_super_block(&sblock) || sblock.free_inode_count == 0) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    const vint_t file_size = ftell(file);
    rewind(file);

    const vint_t required_full_blocks = (file_size / MAX_BLOCK_DATA);
    const vint_t required_partial_block = (file_size % MAX_BLOCK_DATA != 0 ? 1 : 0);
    const vint_t required_blocks = required_full_blocks + required_partial_block;

    if(sblock.free_block_count < required_blocks) {
        return -1;
    }

    const vint_t first_free_block_offset = fseek_first_free_block(disk, &sblock);

    {
        fseek_first_free_inode(disk, &sblock);

        struct inode new_inode = {
            .file_name = {'\0'},
            .file_size = file_size,
            .first_block_offset = first_free_block_offset
        };
        strncpy(new_inode.file_name, file_name, sizeof(new_inode.file_name));

        write_inode(disk, &new_inode);
    }

    fseek(disk, first_free_block_offset, SEEK_SET);
    vint_t block_offset = first_free_block_offset;

    for(vint_t i = 0; i < required_full_blocks; ++i) {
        struct block block;
        fread(block.data, sizeof(unsigned char), MAX_BLOCK_DATA, file);

        if(required_partial_block == 0 && i == required_blocks-1) {
            block.next_block_offset = END_BLOCK_MARK;
        } else {
            block.next_block_offset = fseek_next_free_block(disk);
        }

        fseek(disk, block_offset, SEEK_SET);
        write_block(disk, &block);

        block_offset = block.next_block_offset;
        fseek(disk, block_offset, SEEK_SET);
    }

    if(required_partial_block) {
        const vint_t remaining_bytes = file_size % MAX_BLOCK_DATA;

        struct block block;
        fread(block.data, sizeof(unsigned char), remaining_bytes, file);
        memset(block.data + remaining_bytes, 0, MAX_BLOCK_DATA - remaining_bytes);

        block.next_block_offset = END_BLOCK_MARK;
        write_block(disk, &block);
    }

    --sblock.free_inode_count;
    sblock.free_block_count -= required_blocks;
    write_super_block(disk, &sblock);
    return 0;
}

int vfs_copy_from_virtual_to_native(FILE* disk, const char* file_name) {
    /// @todo
    return 0;
}
