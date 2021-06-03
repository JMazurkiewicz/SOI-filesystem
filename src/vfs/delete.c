/// @author Jakub Mazurkiewicz

#include <stdio.h>

int vfs_delete(const char* disk_name) {
    return remove(disk_name);
}
