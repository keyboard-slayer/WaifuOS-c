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

#include <arch/abstract.h>
#include <arch/cross-x86/madt.h>
#include <arch/cross-x86/pit.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <macro.h>
#include <stddef.h>

#include "asm.h"
#include "ioapic.h"
#include "lapic.h"

static uintptr_t lapic_addr;

static uint32_t
lapic_read(uint32_t reg)
{
	return *((volatile uint32_t *) (lapic_addr + reg));
}

static void
lapic_write(uint32_t reg, uint32_t value)
{
	*((volatile uint32_t *) (lapic_addr + reg)) = value;
}

void
lapic_timer_init(void)
{
	uint32_t ticks;

	lapic_write(LAPIC_TPR, 0);

	lapic_write(LAPIC_TIMER_DIV, LAPIC_DIVIDE_BY_16);
	lapic_write(LAPIC_INIT, 0xffffffff);

	pit_sleep(10);

	lapic_write(LAPIC_TIMER_REG, LAPIC_TIMER_MASK);

	ticks = 0xffffffff - lapic_read(LAPIC_CURRENT);

	lapic_write(LAPIC_TIMER_REG, IRQ(0) | LAPIC_TIMER_PERIODIC);
	lapic_write(LAPIC_TIMER_DIV, LAPIC_DIVIDE_BY_16);
	lapic_write(LAPIC_INIT, ticks);
}

void
lapic_eoi(void)
{
	lapic_write(LAPIC_EOI, 0);
}

int
lapic_current_cpu(void)
{
	if (lapic_addr == 0)
	{
		return 0;
	}

	return lapic_read(LAPIC_CPU_ID) >> 24;
}

void
lapic_init(void)
{
	lapic_addr = madt_get_lapic_addr() + loader_get_hhdm();
	debug_println(DEBUG_INFO, "Found lapic at %p", lapic_addr);

	asm_write_msr(MSR_APICBASE, (asm_read_msr(MSR_APICBASE) | LAPIC_ENABLE) & ~((1 << 10)));
	lapic_write(LAPIC_SPURIOUS, lapic_read(LAPIC_SPURIOUS) | 0x1ff);

	lapic_timer_init();
}
