/// @author Jakub Mazurkiewicz

#include <stdio.h>

void vfs_delete(const char* disk_name) {
    if(remove(disk_name) == 0) {
        printf("svfs: disk \"%s\" has been removed\n", disk_name);
    } else {
        printf("svfs: unable to remove \"%s\" disk\n", disk_name);
    }
}
