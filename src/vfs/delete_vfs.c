/// @author Jakub Mazurkiewicz
#include <stdio.h>

void delete_vfs(const char* name) {
    if(remove(name) == 0) {
        printf("svfs: disk \"%s\" has been removed\n", name);
    } else {
        printf("svfs: unable to remove \"%s\" disk\n", name);
    }
}
