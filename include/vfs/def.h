/// @author Jakub Mazurkiewicz

#ifndef VFS_DEF_H
#define VFS_DEF_H

#include <inttypes.h>
#include <stdint.h>

typedef uint32_t vint_t;
#define SCNVINT SCNu32

#define BLOCK_SIZE ((vint_t)4096)

#endif