#include "arch/x86_64/tss.h"
#include <arch/cross-x86/gdt.h>

static gdt_t gdt;
static tss_t tss;
static gdtr_t gdt_descriptor = { sizeof(gdt_t) - 1, (uintptr_t) &gdt };

static void
gdt_init_entry(gdt_entry_t *self, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	self->limit_high_flags = ((limit >> 16) & 0xF) | (flags & 0xF);
	self->access = GDT_PRESENT | GDT_RW | GDT_SEGMENT | access;

	self->base_low = base & 0xFFFF;
	self->base_middle = (base >> 16) & 0xFF;
	self->base_high = (base >> 24) & 0xFF;

	self->limit_low = limit & 0xFFFF;
}

static tss_entry_t
init_tss(uintptr_t tss)
{
	tss_entry_t ret;

	ret.base_low16 = (uint16_t) tss & 0xffff;
	ret.base_mid8 = (uint8_t) (tss >> 16) & 0xff;
	ret.base_high8 = (uint8_t) (tss >> 24) & 0xff, ret.base_upper32 = tss >> 32;
	ret.base_upper32 = tss >> 32;

	ret.length = sizeof(tss_entry_t);
	ret.flags1 = 0x89;
	ret.flags2 = 0;
	ret.reserved = 0;

	return ret;
}

void
gdt_init(void)
{
	gdt_init_entry(&gdt.entries[GDT_NULL], 0, 0, 0, 0);

	gdt_init_entry(&gdt.entries[GDT_KERNEL_CODE], 0, 0, GDT_EXECUTABLE, GDT_LONG_MODE | GDT_GRANULARITY);
	gdt_init_entry(&gdt.entries[GDT_KERNEL_DATA], 0, 0, GDT_RW, GDT_LONG_MODE | GDT_GRANULARITY);

	gdt_init_entry(&gdt.entries[GDT_USER_CODE], 0, 0, GDT_EXECUTABLE | GDT_USER_MODE, GDT_LONG_MODE | GDT_GRANULARITY);
	gdt_init_entry(&gdt.entries[GDT_USER_DATA], 0, 0, GDT_RW | GDT_USER_MODE, GDT_LONG_MODE | GDT_GRANULARITY);

	gdt.tss_entry = init_tss((uintptr_t) &tss);

	gdt_flush((uintptr_t) &gdt_descriptor);
}
