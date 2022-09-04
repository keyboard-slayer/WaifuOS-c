#ifndef LOADER_ABSTRACT_H
#define LOADER_ABSTRACT_H

#include <macro.h>
#include <stddef.h>
#include <stdint.h>

#define LIMIT_ENTRIES 64

typedef enum
{
	MEMMAP_USABLE,
	MEMMAP_RESERVED,
	MEMMAP_RECLAIMABLE,
	MEMMAP_BAD_MEMORY,
	MEMMAP_BOOTLOADER_RECLAIMABLE,
	MEMMAP_KERNEL_AND_MODULES,
	MEMMAP_FRAMEBUFFER
} memmap_type_t;

typedef struct
{
	uintptr_t base;
	size_t length;
	memmap_type_t type;
} memmap_t;

typedef struct
{
	memmap_t entries[LIMIT_ENTRIES];
	size_t length;
} memmaps_t;

uintptr_t loader_get_kfile(void);
size_t loader_get_hhdm(void);
memmaps_t *loader_get_memmaps(void);

#endif /* !LOADER_ABSTRACT_H */
