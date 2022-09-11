/**
 * Copyright (C) 2022 Keyboard Slayer
 *
 * This file is part of WaifuOS.
 *
 * WaifuOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WaifuOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOADER_ABSTRACT_H
#define LOADER_ABSTRACT_H

#include <macro.h>
#include <mem.h>
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

typedef struct
{
	uintptr_t addr;
	uint64_t width;
	uint64_t height;
	uint64_t pitch;
	uint64_t bpp;
} fb_t;

typedef struct
{
	void *ptr;
	size_t size;
} module_t;

module_t loader_get_kfile(void);
size_t loader_get_hhdm(void);
memmaps_t *loader_get_memmaps(void);
fb_t loader_get_framebuffer(void);
module_t loader_get_module(char const *);
virtual_physical_map_t loader_get_kaddr(void);
size_t loader_get_stack_size(void);
void *loader_get_rsdp(void);

#endif /* !LOADER_ABSTRACT_H */
