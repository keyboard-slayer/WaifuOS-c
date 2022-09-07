#ifndef LIBC_EXT_MEM_H
#define LIBC_EXT_MEM_H

#include <stdint.h>

typedef struct
{
	uintptr_t physical;
	uintptr_t virtual;
	uintptr_t length;
} virtual_physical_map_t;

#endif /* !LIBC_EXT_MEM_H */
