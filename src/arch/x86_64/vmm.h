#ifndef ARCH_X86_64_VMM_H
#define ARCH_X86_64_VMM_H

/* PAGING HELL IS REAL */

#include <macro.h>
#include <stddef.h>
#include <stdint.h>

#define FOUR_GIG					0x100000000
#define PMLX_GET_INDEX(addr, level) (((uint64_t) addr & ((uint64_t) 0x1ff << (12 + level * 9))) >> (12 + level * 9))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
typedef struct
{
	uint8_t present : 1;
	uint8_t read_write : 1;
	uint8_t user : 1;
	uint8_t caching : 1;
	uint8_t caching_disable : 1;
	uint8_t accessed : 1;
	uint8_t dirty : 1;
	uint8_t huge_page : 1;
	uint8_t global_page : 1;
	uint8_t _available : 3;
	uint64_t physical : 52;
} PACKED pml_entry_t;
#pragma GCC diagnostic pop

typedef struct
{
	pml_entry_t entries[512];
} __attribute__((packed)) pml_t;

typedef struct
{
	uintptr_t physical;
	uintptr_t virtual;
	uintptr_t length;
} virtual_physical_map_t;

void vmm_init(void);

#endif /* !ARCH_X86_64_VMM_H */
