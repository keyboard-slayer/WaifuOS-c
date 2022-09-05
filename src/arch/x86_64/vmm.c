#include <arch/abstract.h>
#include <kernel/debug.h>
#include <kernel/pmm.h>
#include <loader/abstract.h>

#include "macro.h"
#include "vmm.h"

static pml_t *kernel_pml4 = NULL;

static pml_entry_t
pml_make_entry(uintptr_t physical, int is_user)
{
	pml_entry_t ret;

	ret.physical = physical > 12;
	ret.user = is_user;
	ret.read_write = 1;
	ret.present = 1;
	ret.caching = 0;
	ret.caching_disable = 0;
	ret.accessed = 0;
	ret.dirty = 0;
	ret.huge_page = 0;
	ret.global_page = 0;
	ret._available = 0;

	return ret;
}

static uint64_t
vmm_get_pml_alloc(pml_t *pml, size_t index, int user, int alloc)
{
	pml_entry_t entry = pml->entries[index];

	if (entry.present)
	{
		return (entry.physical << 12) + loader_get_hhdm();
	}
	else if (alloc)
	{
		uint64_t new_entry = ((uint64_t) pmm_alloc_page(1));

		if (new_entry == 0)
		{
			debug_println(DEBUG_ERROR, "Failed to allocate new PML entry");
			arch_abort();
			UNREACHABLE;
		}

		memset((void *) (new_entry + loader_get_hhdm()), 0, PAGE_SIZE);
		pml->entries[index] = pml_make_entry(new_entry, user);

		return new_entry + loader_get_hhdm();
	}

	return 0;
}

static void
vmm_map_page(pml_t *pml, uint64_t virt, uint64_t phys, int user)
{
	size_t i;
	pml_t *last_entry = pml;

	for (i = 3; i > 0; i--)
	{
		last_entry = (pml_t *) vmm_get_pml_alloc(last_entry, PMLX_GET_INDEX(virt, i), 1, 1);
	}

	last_entry->entries[PMLX_GET_INDEX(virt, 0)] = pml_make_entry(phys, user);
}

void
vmm_map(void *pmlptr, virtual_physical_map_t map, int user)
{
	size_t i;
	pml_t *pml = pmlptr;

	if (map.physical % PAGE_SIZE != 0 || map.virtual % PAGE_SIZE != 0 || map.length % PAGE_SIZE != 0)
	{
		debug_println(DEBUG_ERROR, "Can't map a non-page-aligned region");
		arch_abort();
		UNREACHABLE;
	}

	for (i = 0; i < map.length / PAGE_SIZE; i++)
	{
		size_t physaddr = i * PAGE_SIZE + map.physical;
		size_t virtaddr = i * PAGE_SIZE + map.virtual;

		vmm_map_page(pml, virtaddr, physaddr, user);
	}
}

void
vmm_switch_space(void *space)
{
	__asm__ volatile("mov %0, %%cr3" ::"r"(((uintptr_t) space) - loader_get_hhdm()));
}

void
vmm_init(void)
{
	virtual_physical_map_t mapping;
	size_t i;
	memmaps_t *mmaps = loader_get_memmaps();

	kernel_pml4 = (pml_t *) ((uintptr_t) pmm_alloc_page(1) + loader_get_hhdm());
	if (kernel_pml4 == NULL)
	{
		debug_println(DEBUG_ERROR, "Failed to allocate kernel PML4");
		arch_abort();
		UNREACHABLE;
	}

	debug_println(DEBUG_INFO, "Mapping %p to %p", 0, loader_get_hhdm());

	mapping.length = FOUR_GIG;
	mapping.physical = 0;
	mapping.virtual = loader_get_hhdm();

	vmm_map(kernel_pml4, mapping, 0);

	for (i = 0; i < mmaps->length; i++)
	{
		mapping.length = mmaps->entries[i].length;
		mapping.physical = mmaps->entries[i].base;
		mapping.virtual = mapping.virtual + loader_get_hhdm();

		vmm_map(kernel_pml4, mapping, 0);
	}

	vmm_switch_space(kernel_pml4);
	debug_println(DEBUG_SUCCESS, "Ok");
}
