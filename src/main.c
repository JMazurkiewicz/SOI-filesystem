/// @author Jakub Mazurkiewicz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "vfs.h"

void do_new(int argc, char** argv) {
    if(argc != 2) {
        puts("usage: ./svfs new <disk name> <size in bytes>");
        return;
    }

    vint_t disk_size = 0;
    if(sscanf(argv[1], "%"SCNVINT, &disk_size) != 1) {
        puts("svfs new: invalid file_size argument");
    }

    const char* const disk_name = argv[0];
    if(vfs_new(disk_name, disk_size) != 0) {
        printf("svfs new: unable to create \"%s\" disk file\n", disk_name);
    }
}

void do_copy(int argc, char** argv) {
    if(argc != 5 || strcmp(argv[0], "from") != 0 || strcmp(argv[2], "to") != 0) {
        puts("usage: ./svfs copy from <source> to <target> <file name>");
        return;
    }

    const char* disk_name;
    enum copy_direction { TO_VIRTUAL, TO_NATIVE } direction;
    
    {
        const char* const source = argv[1];
        const char* const target = argv[3];

        if(strcmp(source, "native") == 0) {
            disk_name = target;
            direction = TO_VIRTUAL;
        } else if(strcmp(target, "native") == 0) {
            disk_name = source;
            direction = TO_NATIVE;
        } else {
            puts("svfs copy: <source> or <target> must be 'native'");
            return;
        }
    }

    FILE* const disk = fopen(disk_name, "r+b");
    if(disk == NULL) {
        printf("svfs copy: unable to open \"%s\" disk file\n", disk_name);
        return;
    }

    const char* const file_name = argv[4];

    if(direction == TO_VIRTUAL) {
        FILE* const file = fopen(file_name, "rb");
        if(file == NULL) {
            printf("svfs copy: unable to open \"%s\" file for copying\n", file_name);
        } else {
            vfs_copy_from_native_to_virtual(disk, file);
        }
    } else {
        vfs_copy_from_virtual_to_native(disk, file_name);
    }
    
    fclose(disk);
}

void do_print(int argc, char** argv) {

}

void do_stats(int argc, char** argv) {

}

void do_remove(int argc, char** argv) {
    const char* const file_name = argv[0];


}

void do_delete(int argc, char** argv) {
    const char* const disk_name = argv[0];
    vfs_delete(disk_name);
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        display_help();
    } else {
        const char* option = argv[1];
        const int argc2 = argc - 2;
        char** const argv2 = argv + 2;

        if(strcmp(option, "new") == 0) {
            do_new(argc2, argv2);
        } else if(strcmp(option, "copy") == 0) {
            do_copy(argc2, argv2);
        } else if(strcmp(option, "print") == 0) {
            do_print(argc2, argv2);
        } else if(strcmp(option, "stats") == 0) {
            do_stats(argc2, argv2);
        } else if(strcmp(option, "remove") == 0) {
            do_remove(argc2, argv2);
        } else if(strcmp(option, "delete") == 0) {
            do_delete(argc2, argv2);
        } else if(strcmp(option, "help") == 0) {
            display_help();
        } else {
            printf("Unrecognized option \"%s\".\n", option);
            display_help();
        }
    }
}
