#include <loader/abstract.h>
#include <stddef.h>

#include "limine.h"

extern void bootstrap(void);

static memmaps_t memmaps = { 0 };

/* clang-format off */
volatile struct limine_entry_point_request entry_point = {
	.id = LIMINE_ENTRY_POINT_REQUEST,
	.entry = bootstrap
};

volatile struct limine_kernel_file_request kfile_req = {
	.id = LIMINE_KERNEL_FILE_REQUEST
};

volatile struct limine_hhdm_request hhdm_req = {
	.id = LIMINE_HHDM_REQUEST
};

volatile struct limine_memmap_request mmap_req = {
	.id = LIMINE_MEMMAP_REQUEST
};

/* clang-format on */

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
