/// @author Jakub Mazurkiewicz

#include "vfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char DISK_EXT[] = ".vd";

static void vfs_form_disk(FILE* disk, vint_t size);

int vfs_new(const char* disk_name, vint_t size) {
    const size_t file_name_length = strlen(disk_name) + sizeof(DISK_EXT);
    char* file_name = malloc(file_name_length);

    strcpy(file_name, disk_name);
    strcat(file_name, DISK_EXT);

    FILE* const disk = fopen(file_name, "wb+");
    if(disk == NULL) {
        return -1;
    }

    vfs_form_disk(disk, size);

    fclose(disk);
    free(file_name);
    return 0;
}

void vfs_form_disk(FILE* disk, vint_t size) {
    /// @todo Create a disk.
}
