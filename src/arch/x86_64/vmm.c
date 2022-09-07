#include <arch/abstract.h>
#include <kernel/debug.h>
#include <kernel/pmm.h>
#include <loader/abstract.h>

#include "cpuid.h"
#include "macro.h"
#include "mem.h"
#include "vmm.h"

static uintptr_t *kernel_pml4 = NULL;

extern char text_start_addr[];
extern char text_end_addr[];
extern char rodata_start_addr[];
extern char rodata_end_addr[];
extern char data_start_addr[];
extern char data_end_addr[];

static uintptr_t *
vmm_get_pml_alloc(uintptr_t *pml, size_t index, int alloc)
{
	if ((pml[index] & VMM_PRESENT) != 0)
	{
		return (uintptr_t *) (VMM_GET_ADDR(pml[index]) + loader_get_hhdm());
	}
	else if (alloc)
	{
		uintptr_t new_entry = (uintptr_t) pmm_alloc_page(1);
		if (new_entry == 0)
		{
			return NULL;
		}

		memset((void *) (new_entry + loader_get_hhdm()), 0, PAGE_SIZE);
		pml[index] = new_entry | VMM_PRESENT | VMM_WRITABLE | VMM_USER;
		return (void *) ((uintptr_t) new_entry + loader_get_hhdm());
	}

	return 0;
}

static int
vmm_map_page(uintptr_t *pml, uint64_t virt, uint64_t phys, uint64_t flags, int huge)
{
	size_t pml1_entry = PMLX_GET_INDEX(virt, 0);
	size_t pml2_entry = PMLX_GET_INDEX(virt, 1);
	size_t pml3_entry = PMLX_GET_INDEX(virt, 2);
	size_t pml4_entry = PMLX_GET_INDEX(virt, 3);

	uintptr_t *pml3;
	uintptr_t *pml2;
	uintptr_t *pml1;

	pml3 = vmm_get_pml_alloc(pml, pml4_entry, 1);
	if (!pml3)
	{
		return 1;
	}

	if (cpuid_has_1gb_page() && huge)
	{
		pml3[pml3_entry] = phys | flags | VMM_HUGE;
		return 0;
	}

	pml2 = vmm_get_pml_alloc(pml3, pml3_entry, 1);
	if (!pml2)
	{
		return 1;
	}

	if (huge)
	{
		pml2[pml2_entry] = phys | flags | VMM_HUGE;
		return 0;
	}

	pml1 = vmm_get_pml_alloc(pml2, pml2_entry, 1);
	if (!pml1)
	{
		return 1;
	}

	pml1[pml1_entry] = phys | flags;
	return 0;
}

void
vmm_switch_space(void *space)
{
	/* clang-format off */
	__asm__ volatile(
		"mov %0, %%cr3" 
		:: "r" ((uintptr_t) space - loader_get_hhdm())
		: "memory"
	);
}

static int
vmm_map_section_range(uintptr_t start, uintptr_t end, uint64_t flags)
{
	uintptr_t i;
	virtual_physical_map_t kaddr = loader_get_kaddr();

	for (i = ALIGN_DOWN(start, PAGE_SIZE); i < ALIGN_UP(end, PAGE_SIZE); i += PAGE_SIZE)
	{
		uintptr_t phys = i - kaddr.virtual + kaddr.physical;
		if (vmm_map_page(kernel_pml4, i, phys, flags, 0))
		{
			return 1;
		}
	}

	return 0;
}

void
vmm_init(void)
{
	size_t i;
	memmaps_t *mmaps = loader_get_memmaps();
	size_t page_size = MIB(2);

	if (cpuid_has_1gb_page())
	{
		debug_println(DEBUG_INFO, "1GB pages are supported");
	}

	kernel_pml4 = (uint64_t *) pmm_alloc_page(1);
	if (kernel_pml4 == NULL)
	{
		debug_println(DEBUG_ERROR, "Failed to allocate kernel PML4");
		arch_abort();
		UNREACHABLE;
	}

	kernel_pml4 = (uint64_t *) ((uintptr_t) kernel_pml4 + loader_get_hhdm());
	memset(kernel_pml4, 0, PAGE_SIZE);

	if (vmm_map_section_range((uintptr_t) text_start_addr, (uintptr_t) text_end_addr, VMM_PRESENT))
	{
		debug_println(DEBUG_ERROR, "Couldn't map .text");
		arch_abort();
		UNREACHABLE;
	}

	if (vmm_map_section_range((uintptr_t) rodata_start_addr, (uintptr_t) rodata_end_addr, VMM_PRESENT | VMM_NOEXE))
	{
		debug_println(DEBUG_ERROR, "Couldn't map .rodata");
		arch_abort();
		UNREACHABLE;
	}

	if (vmm_map_section_range((uintptr_t) data_start_addr, (uintptr_t) data_end_addr,
							  VMM_PRESENT | VMM_WRITABLE | VMM_NOEXE))
	{
		debug_println(DEBUG_ERROR, "Couldn't map .data");
		arch_abort();
		UNREACHABLE;
	}

	for (i = page_size; i < MAX(GIB(4), pmm_available_pages() * PAGE_SIZE); i += page_size)
	{
		if (vmm_map_page(kernel_pml4, i + loader_get_hhdm(), i, VMM_PRESENT | VMM_WRITABLE, 1))
		{
			debug_println(DEBUG_ERROR, "Couldn't map 4gib");
			arch_abort();
			UNREACHABLE;
		}
	}

	for (i = 0; i < mmaps->length; i++)
	{
		size_t j;

		for (j = 0; j < ALIGN_UP(mmaps->entries[i].length, page_size); j += page_size)
		{
			if (vmm_map_page(kernel_pml4, ALIGN_DOWN(mmaps->entries[i].base, page_size) + j + loader_get_hhdm(), ALIGN_DOWN(mmaps->entries[i].base, page_size) + j , VMM_PRESENT | VMM_WRITABLE | VMM_NOEXE , 1))
			{
				debug_println(DEBUG_ERROR, "Couldn't map mmap");
				arch_abort();
				UNREACHABLE;
			}
		}
	}

	vmm_switch_space(kernel_pml4);
	debug_println(DEBUG_SUCCESS, "Ok");
}
