/// @author Jakub Mazurkiewicz

#include "vfs.h"

static const char* const BAR = "--------------------------------------";

int vfs_stats(FILE* disk) {
    const struct super_block sblock = load_super_block(disk);
    if(!validate_super_block(&sblock)) {
        return -1;
    }

    printf("Disk size: %"PRIVINT"\n", sblock.disk_size);
    puts(BAR);
    printf("Total inodes: %"PRIVINT"\n", sblock.inode_count);
    printf("Free inodes: %"PRIVINT"\n", sblock.free_inode_count);
    printf("Occupied inodes: %"PRIVINT"\n", sblock.inode_count - sblock.free_inode_count);
    printf("First inode offset: %"PRIVINT"\n", sblock.first_inode_offset);
    puts(BAR);
    printf("Total blocks: %"PRIVINT"\n", sblock.block_count);
    printf("Free blocks: %"PRIVINT"\n", sblock.free_block_count);
    printf("Occupied blocks: %"PRIVINT"\n", sblock.block_count - sblock.free_block_count);
    printf("First block offset: %"PRIVINT"\n", sblock.first_block_offset);

    return 0;
}
