/// @author Jakub Mazurkiewicz

#include "vfs.h"

int vfs_print(FILE* disk) {
    const struct super_block sblock = load_super_block(disk);
    if(!validate_super_block(&sblock)) {
        return -1;
    }

    const vint_t taken_inodes = count_taken_inodes(&sblock);
    if(taken_inodes == 0) {
        return 0;
    }

    fseek(disk, sblock.first_inode_offset, SEEK_SET);
    
    puts("File name                       | Size in bytes | Disk offset  ");
    puts("--------------------------------+---------------+--------------");

    for(vint_t i = 0; i < sblock.inode_count; ++i) {
        const struct inode inode = load_inode(disk);

        printf("%-32s| %-14d| %13d\n", inode.file_name, inode.file_size, inode.first_block_offset);
    }

    return 0;
}
