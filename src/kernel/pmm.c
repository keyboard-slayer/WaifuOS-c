#include <arch/abstract.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <macro.h>

#include "pmm.h"

static uint8_t *bitmap = NULL;
static size_t bitmap_size = 0;
static size_t last_used_index = 0;
static size_t available_pages = 0;

void
pmm_free(uint64_t base, uint64_t length)
{
	size_t i;

	for (i = 0; i < length; i++)
	{
		bitmap[(i + base) / 8] &= ~(1 << ((i + base) % 8));
		available_pages++;
	}
}

static void
pmm_set_used(uint64_t base, uint64_t length)
{
	size_t i;

	for (i = 0; i < length; i++)
	{
		bitmap[(i + base) / 8] |= (1 << ((i + base) % 8));
		available_pages--;
	}

	available_pages -= length;
}

static int
bitmap_is_bit_set(size_t index)
{
	return bitmap[index / 8] & (1 << (index % 8));
}

static void *
pmm_inner(size_t pages)
{
	size_t page_start_index;
	void *ret;
	size_t size = 0;

	while (last_used_index < bitmap_size)
	{
		if (!bitmap_is_bit_set(last_used_index++))
		{
			if (++size == pages)
			{
				page_start_index = last_used_index - pages;
				pmm_set_used(page_start_index, pages);

				ret = (void *) (page_start_index * PAGE_SIZE);
				return ret;
			}
		}
		else
		{
			size = 0;
		}
	}

	debug_println(DEBUG_ERROR, "Out of memory");
	return NULL;
}

void *
pmm_alloc_page(size_t pages)
{
	void *ret = pmm_inner(pages);

	if (ret == NULL)
	{
		last_used_index = 0;
		ret = pmm_inner(pages);
	}

	if (ret == NULL)
	{
		debug_println(DEBUG_ERROR, "Out of memory");
	}

	return ret;
}

void *
pmm_alloc(size_t size)
{
	return pmm_alloc_page(size / PAGE_SIZE);
}

void
pmm_init(void)
{
	size_t i;
	memmap_t last;
	memmap_t *entry;
	memmaps_t *memmaps = loader_get_memmaps();
	uint64_t hhdm = loader_get_hhdm();

	if (hhdm == 0)
	{
		debug_println(DEBUG_ERROR, "Couldn't get kernel HHDM offset");
		arch_abort();
		UNREACHABLE;
	}

	if (memmaps == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't get memory maps");
		arch_abort();
		UNREACHABLE;
	}

	last = memmaps->entries[memmaps->length - 1];
	bitmap_size = ALIGN_UP((last.base + last.length) / (PAGE_SIZE * 8), PAGE_SIZE);
	debug_println(DEBUG_INFO, "bitmap size: %zu bytes.", bitmap_size);

	for (i = 0; i < memmaps->length; i++)
	{
		entry = &memmaps->entries[i];
		if (entry->type == MEMMAP_USABLE && entry->length >= bitmap_size)
		{
			bitmap = (uint8_t *) (entry->base + hhdm);
			debug_println(DEBUG_INFO, "PMM bitmap allocated at %p.", bitmap);

			entry->base += bitmap_size;
			entry->length -= bitmap_size;
			break;
		}
	}

	if (bitmap == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't allocate the memory bitmap");
		arch_abort();
		UNREACHABLE;
	}

	memset(bitmap, 0xff, bitmap_size);

	for (i = 0; i < memmaps->length; i++)
	{
		entry = &memmaps->entries[i];

		if (entry->type == MEMMAP_USABLE)
		{
			pmm_free(ALIGN_DOWN(entry->base, PAGE_SIZE) / PAGE_SIZE, ALIGN_UP(entry->length, PAGE_SIZE) / PAGE_SIZE);
		}
	}

	pmm_set_used((((uintptr_t) bitmap) - hhdm) / PAGE_SIZE, bitmap_size / PAGE_SIZE);
	debug_println(DEBUG_SUCCESS, "Ok");
}

size_t
pmm_available_pages(void)
{
	return available_pages;
}
