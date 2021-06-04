/// @author Jakub Mazurkiewicz

#include "vfs.h"

int vfs_delete(const char* disk_name) {
    return remove(disk_name);
}
