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

#include <abstract/loader.h>
#include <stddef.h>
#include <string.h>

#include "limine.h"

extern void bootstrap(void);

static memmaps_t memmaps = { 0 };

volatile struct limine_entry_point_request entry_point = { LIMINE_ENTRY_POINT_REQUEST, 0, 0, bootstrap };
volatile struct limine_kernel_file_request kfile_req = { LIMINE_KERNEL_FILE_REQUEST, 0, 0 };
volatile struct limine_hhdm_request hhdm_req = { LIMINE_HHDM_REQUEST, 0, 0 };
volatile struct limine_memmap_request mmap_req = { LIMINE_MEMMAP_REQUEST, 0, 0 };
volatile struct limine_framebuffer_request fb_req = { LIMINE_FRAMEBUFFER_REQUEST, 0, 0 };
volatile struct limine_module_request module_req = { LIMINE_MODULE_REQUEST, 0, 0 };
volatile struct limine_kernel_address_request kaddr_req = { LIMINE_KERNEL_ADDRESS_REQUEST, 0, 0 };
volatile struct limine_rsdp_request rsdp_req = { LIMINE_RSDP_REQUEST, 0, 0 };

module_t
loader_get_kfile(void)
{
	module_t kfile = { 0 };
	if (kfile_req.response == NULL)
	{
		return kfile;
	}

	kfile.ptr = kfile_req.response->kernel_file->address;
	kfile.size = kfile_req.response->kernel_file->size;
	return kfile;
}

size_t
loader_get_hhdm(void)
{
	if (hhdm_req.response == NULL)
	{
		return 0;
	}

	return hhdm_req.response->offset;
}

memmaps_t *
loader_get_memmaps(void)
{
	size_t i;
	memmap_t *entry;

	if (mmap_req.response == NULL)
	{
		return NULL;
	}

	if (memmaps.length > 0)
	{
		return &memmaps;
	}

	memmaps.length = mmap_req.response->entry_count;

	for (i = 0; i < mmap_req.response->entry_count; i++)
	{
		entry = &memmaps.entries[i];
		entry->base = mmap_req.response->entries[i]->base;
		entry->length = mmap_req.response->entries[i]->length;
		entry->type = mmap_req.response->entries[i]->type;
	}

	return &memmaps;
}

fb_t
loader_get_framebuffer(void)
{
	struct limine_framebuffer *fb;
	fb_t framebuffer = { 0, 0, 0, 0, 0 };

	if (fb_req.response == NULL)
	{
		return framebuffer;
	}

	fb = fb_req.response->framebuffers[0];

	framebuffer.width = fb->width;
	framebuffer.height = fb->height;
	framebuffer.pitch = fb->pitch;
	framebuffer.bpp = fb->bpp;
	framebuffer.addr = (uintptr_t) fb->address;

	return framebuffer;
}

module_t
loader_get_module(char const *name)
{
	size_t i;
	module_t mod = { 0 };

	if (module_req.response == NULL)
	{
		return mod;
	}

	for (i = 0; i < module_req.response->module_count; i++)
	{
		if (memcmp(module_req.response->modules[i]->path, name, strlen(name)) == 0)
		{
			mod.ptr = module_req.response->modules[i]->address;
			mod.size = module_req.response->modules[i]->size;
		}
	}

	return mod;
}

virtual_physical_map_t
loader_get_kaddr(void)
{
	virtual_physical_map_t kaddr = { 0 };

	if (kaddr_req.response == NULL)
	{
		return kaddr;
	}

	kaddr.physical = kaddr_req.response->physical_base;
	kaddr.virtual = kaddr_req.response->virtual_base;

	return kaddr;
}

size_t
loader_get_stack_size(void)
{
	return KIB(64);
}

void *
loader_get_rsdp(void)
{
	if (rsdp_req.response == NULL)
	{
		return NULL;
	}

	return rsdp_req.response->address;
}
