/// @author Jakub Mazurkiewicz

#ifndef VFS_OPEATIONS_H
#define VFS_OPEATIONS_H

#include <stdio.h>

#include "def.h"

int vfs_new(const char* disk_name, vint_t size);

int vfs_copy_from_native_to_virtual(FILE* disk, FILE* file);
int vfs_copy_from_virtual_to_native(FILE* disk, const char* file_name);

void vfs_delete(const char* disk_name);

//void copy_

void vfs_print(const char* disk_name);

void vfs_remove(const char* disk_name, const char* file_name);

#endif