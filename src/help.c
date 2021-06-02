/// @author Jakub Mazurkiewicz

#include <stdio.h>

static const char* const HELP = {
    "Virtual filesystem help:\n"
    "* ./svfs new <disk name> <size in bytes>\n"
    "    Creates new virtual disk.\n"
    "* ./svfs copy from <source> to <target> <file name>\n"
    "    Copies file from 'source' disk to 'target' disk.\n"
    "    Available options for ('source', target') pair are:\n"
    "    - (<disk name>, native),\n"
    "    - (native, <disk name>).\n"
    "* ./svfs print <disk name>\n"
    "    Prints list of files available in virtual disk.\n"
    "* ./svfs stats <disk name>\n"
    "    Displays statistics about disk.\n"
    "* ./svfs remove <file name> from <disk name>\n"
    "    Removes file from virtual disk.\n"
    "* ./svfs delete <disk name>\n"
    "    Deletes virtual disk.\n"
    "* ./svfs help\n"
    "    Displays this screen."
};

void display_help(void) {
    puts(HELP);
}
