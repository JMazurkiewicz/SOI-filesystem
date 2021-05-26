/// @author Jakub Mazurkiewicz

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "vfs.h"

void do_new(int argc, char** argv) {
    if(argc != 2) {
        puts("Usage: ./svfs new file_name file_size");
        return;
    }

    const char* file_name = argv[0];
    size_t size = 0;

    if(sscanf(argv[1], "%zu", &size) != 1) {
        puts("svfs new: invalid file_size argument");
    } else {
        new_vfs(file_name, size);
    }
}

void do_copy(int argc, char** argv) {

}

void do_print(int argc, char** argv) {

}

void do_remove(int argc, char** argv) {

}

void do_delete(int argc, char** argv) {

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
        } else if(strcmp(option, "copy")) {
            do_copy(argc2, argv2);
        } else if(strcmp(option, "print")) {
            do_print(argc2, argv2);
        } else if(strcmp(option, "remove")) {
            do_remove(argc2, argv2);
        } else if(strcmp(option, "delete")) {
            do_delete(argc2, argv2);
        } else if(strcmp(option, "help")) {
            display_help();
        } else {
            printf("Unrecognized option \"%s\".\n", option);
            display_help();
        }
    }
}
