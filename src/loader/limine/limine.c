#include <loader/abstract.h>
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

uintptr_t
loader_get_kfile(void)
{
	if (kfile_req.response == NULL)
	{
		return 0;
	}

	return (uintptr_t) kfile_req.response->kernel_file->address;
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

void *
loader_get_module(char const *name)
{
	size_t i;

	if (module_req.response == NULL)
	{
		return NULL;
	}

	for (i = 0; i < module_req.response->module_count; i++)
	{
		if (memcmp(module_req.response->modules[i]->path, name, strlen(name)) == 0)
		{
			return module_req.response->modules[i]->address;
		}
	}

	return NULL;
}