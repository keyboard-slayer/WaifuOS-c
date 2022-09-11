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

#include <arch/cross-x86/acpi.h>
#include <arch/cross-x86/asm.h>
#include <arch/cross-x86/gdt.h>
#include <arch/cross-x86/idt.h>
#include <arch/cross-x86/madt.h>
#include <arch/cross-x86/pit.h>
#include <arch/cross-x86/simd.h>
#include <kernel/debug.h>

#include "ioapic.h"
#include "lapic.h"
#include "vmm.h"

void
arch_init(void)
{
	gdt_init();
	idt_init();
	vmm_init();
	pit_init();
	acpi_init();
	madt_init();
	lapic_init();
	ioapic_init();
	asm_sti();
	simd_init();

	debug_println(DEBUG_SUCCESS, "Arch initialised");
}
