/// @author Jakub Mazurkiewicz

#include "vfs.h"

struct super_block scan_super_block(FILE* disk) {
    rewind(disk);
    
    struct super_block sblock;
    fread(&sblock, sizeof(struct super_block), 1, disk);

    return sblock;
}

void print_super_block(FILE* disk, struct super_block* sblock) {
    rewind(disk);

    fwrite(sblock, sizeof(struct super_block), 1, disk);
}
