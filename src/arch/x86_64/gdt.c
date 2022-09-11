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

#include <arch/cross-x86/gdt.h>
#include <kernel/debug.h>

#include "tss.h"

static gdt_t gdt;
static tss_t tss;
static gdtr_t gdt_descriptor;

static void
gdt_init_entry(gdt_entry_t *self, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
	self->flags = flags;

	self->access = GDT_PRESENT | GDT_RW | GDT_SEGMENT | access;

	self->base_low = base & 0xffff;
	self->base_middle = (base >> 16) & 0xff;
	self->base_high = (base >> 24) & 0xff;

	self->limit_low = limit & 0xffff;
	self->limit_high = (limit >> 16) & 0x0f;
}

static tss_entry_t
init_tss(uintptr_t tss_ptr)
{
	tss_entry_t ret;

	ret.base_low16 = (uint16_t) tss_ptr & 0xffff;
	ret.base_mid8 = (uint8_t) (tss_ptr >> 16) & 0xff;
	ret.base_high8 = (uint8_t) (tss_ptr >> 24) & 0xff;
	ret.base_upper32 = tss_ptr >> 32;

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

	gdt_init_entry(&gdt.entries[GDT_KERNEL_CODE], 0, 0xFFFFFFFF, GDT_EXECUTABLE, GDT_LONG_MODE | GDT_GRANULARITY);
	gdt_init_entry(&gdt.entries[GDT_KERNEL_DATA], 0, 0xFFFFFFFF, GDT_RW, GDT_LONG_MODE | GDT_GRANULARITY);

	gdt_init_entry(&gdt.entries[GDT_USER_CODE], 0, 0xFFFFFFFF, GDT_EXECUTABLE | GDT_USER_MODE,
				   GDT_LONG_MODE | GDT_GRANULARITY);
	gdt_init_entry(&gdt.entries[GDT_USER_DATA], 0, 0xFFFFFFFF, GDT_RW | GDT_USER_MODE, GDT_LONG_MODE | GDT_GRANULARITY);

	gdt.tss_entry = init_tss((uintptr_t) &tss);

	gdt_descriptor.size = sizeof(gdt_t) - 1;
	gdt_descriptor.offset = (uintptr_t) &gdt;

	gdt_flush((uintptr_t) &gdt_descriptor);
}
