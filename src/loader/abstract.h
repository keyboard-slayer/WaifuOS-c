#ifndef LOADER_ABSTRACT_H
#define LOADER_ABSTRACT_H

#include <macro.h>
#include <stddef.h>
#include <stdint.h>

#define LIMIT_ENTRIES 64

/* clang-format off */

#define FOREACH_MEMMAP_TYPE(FUNC)         \
    FUNC(MEMMAP_USABLE)                   \
    FUNC(MEMMAP_RESERVED)                 \
    FUNC(MEMMAP_RECLAIMABLE)              \
    FUNC(MEMMAP_BAD_MEMORY)               \
    FUNC(MEMMAP_BOOTLOADER_RECLAIMABLE)   \
    FUNC(MEMMAP_KERNEL_AND_MODULES)       \
    FUNC(MEMMAP_FRAMEBUFFER)

typedef enum
{
    FOREACH_MEMMAP_TYPE(GENERATE_ENUM)
} memmap_type_t;

USED static char const *mmap_type_str[] = 
{
    FOREACH_MEMMAP_TYPE(GENERATE_STRING)
};

/* clang-format on */

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
