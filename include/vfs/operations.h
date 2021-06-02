/// @author Jakub Mazurkiewicz
#ifndef VFS_OPEATIONS_H
#define VFS_OPEATIONS_H

#include "def.h"

void new_vfs(const char* disk_name, vint_t size);
void delete_vfs(const char* disk_name);

void remove_from_vfs(const char* disk_name, const char* file_name);

void print_vfs(const char* disk_name);

#endif