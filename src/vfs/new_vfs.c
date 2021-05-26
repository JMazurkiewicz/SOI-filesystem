/// @author Jakub Mazurkiewicz
#include "vfs.h"

#include <stdio.h>

void new_vfs(const char* name, vint_t size) {
    FILE* const disk = fopen(name, "wb+");
    if(disk == NULL) {
        printf("svfs: unable to create \"%s\" file\n", name);
        return;
    }

    struct super_block sblock;


    fclose(disk);
}
