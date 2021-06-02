/// @author Jakub Mazurkiewicz
#include "vfs.h"

#include <stdio.h>

void new_vfs(const char* disk_name, vint_t size) {
    FILE* const disk = fopen(disk_name, "wb+");
    if(disk == NULL) {
        printf("svfs: unable to create \"%s\" file\n", disk_name);
        return;
    }

    /// @todo Create a disk.

    fclose(disk);
}
