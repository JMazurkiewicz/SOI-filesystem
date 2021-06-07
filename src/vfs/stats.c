/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static const char* const FREE_MSG = "Free";
static const char* const OCCUPIED_MSG = "Occupied";
static const char* const NONE_MSG = "None";

static void vfs_stats_inodes(FILE* disk, const struct super_block* sblock);
static void vfs_stats_blocks(FILE* disk, const struct super_block* sblock);

int vfs_stats(FILE* disk) {
    const struct super_block sblock = load_super_block(disk);
    if(!validate_super_block(&sblock)) {
        return -1;
    }

    const char* const BAR = "--------------------------------------";

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
    putchar('\n');

    vfs_stats_inodes(disk, &sblock);
    putchar('\n');

    vfs_stats_blocks(disk, &sblock);

    return 0;
}

void vfs_stats_inodes(FILE* disk, const struct super_block* sblock) {
    puts("INode index | Offset     | Status   | File name                       ");
    puts("------------+------------+----------+---------------------------------");

    vint_t offset = sblock->first_inode_offset;

    for(vint_t i = 0; i < sblock->inode_count; ++i) {
        const struct inode current_inode = load_inode(disk);

        const char* const status = (current_inode.first_block_offset == 0 ? FREE_MSG : OCCUPIED_MSG);

        printf("%-11"PRIVINT" | %-10"PRIVINT" | %-8s | %-32s\n", i, offset, status, current_inode.file_name);

        offset += sizeof(struct inode);
    }
}

static void vfs_stats_blocks(FILE* disk, const struct super_block* sblock) {
    char** names = malloc(sizeof(char*) * sblock->inode_count);
    fseek(disk, sblock->first_inode_offset, SEEK_SET);

    char** block_names = malloc(sizeof(char*) * sblock->block_count);

    {
        vint_t inode_offset = sblock->first_inode_offset;

        for(vint_t i = 0; i < sblock->inode_count; ++i) {
            fseek(disk, inode_offset, SEEK_SET);

            const struct inode current_inode = load_inode(disk);

            if(current_inode.first_block_offset == FREE_INODE_MARK) {
                names[i] = NULL;
            } else {
                names[i] = malloc(sizeof(char) * MAX_FILENAME_LENGTH);
                strcpy(names[i], current_inode.file_name);

                vint_t current_block_offset = current_inode.first_block_offset;
                do {
                    fseek(disk, current_block_offset, SEEK_SET);

                    const struct block current_block = load_block(disk);
                    const vint_t next_block_offset = current_block.next_block_offset;

                    const vint_t block_index = calculate_block_index(current_block_offset);
                    block_names[block_index] = names[i];

                    if(next_block_offset == END_BLOCK_MARK) {
                        break;
                    } else {
                        current_block_offset = next_block_offset;
                    }
                } while(true);
            }

            inode_offset += sizeof(struct inode);
        }
    }

    vint_t offset = sblock->first_block_offset;
    fseek(disk, sblock->first_block_offset, SEEK_SET);

    puts("Block index | Offset     | Status   | File name                       ");
    puts("------------+------------+----------+---------------------------------");

    for(vint_t i = 0; i < sblock->block_count; ++i) {
        const struct block current_block = load_block(disk);

        const bool is_free = (current_block.next_block_offset == FREE_BLOCK_MARK);
        const char* status = (is_free ? FREE_MSG : OCCUPIED_MSG);
        const char* name = (is_free ? NONE_MSG : block_names[i]);

        printf("%-11"PRIVINT" | %-10"PRIVINT" | %-8s | %-32s\n", i, offset, status, name);

        offset += sizeof(struct block);
    }

    for(vint_t i = sblock->inode_count; i-- > 0; ){
        free(names[i]);
    }
    free(block_names);
    free(names);
}