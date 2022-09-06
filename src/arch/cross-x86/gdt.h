#ifndef ARCH_CROSS_x86_GDT_H
#define ARCH_CROSS_x86_GDT_H

#include <macro.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __x86_64__
# include "../x86_64/tss.h"
#elif __x86_32__
# error "Not implemented yet"
#endif /* !__x86_64__ || __x86_32__*/

enum gdt_entries
{
	GDT_NULL,
	GDT_KERNEL_CODE,
	GDT_KERNEL_DATA,
	GDT_USER_DATA,
	GDT_USER_CODE,

	GDT_ENTRIES
};

typedef struct
{
	uint16_t size;
	uintptr_t offset;
} PACKED gdtr_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

typedef struct
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t limit_high : 4;
	uint8_t flags : 4;
	uint8_t base_high;
} PACKED gdt_entry_t;

#pragma GCC diagnostic pop

typedef enum
{
	GDT_PRESENT = 1 << 7,
	GDT_USER_MODE = 3 << 5,
	GDT_SEGMENT = 1 << 4,
	GDT_EXECUTABLE = 1 << 3,
	GDT_DIRECTION = 1 << 2,
	GDT_RW = 1 << 1,
	GDT_ACCESS = 0
} gdt_entry_access_t;

typedef enum
{
	GDT_GRANULARITY = 1 << 3,
	GDT_SIZE_FLAG = 1 << 2,
	GDT_LONG_MODE = 1 << 1
} gdt_entry_flags_t;

typedef struct
{
	gdt_entry_t entries[GDT_ENTRIES];
	tss_entry_t tss_entry;
} PACKED gdt_t;

void gdt_init(void);
extern void gdt_flush(uintptr_t);

#endif /* !ARCH_CROSS_X86_GDT_H */
