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
#include <kernel/debug.h>

#include "asm.h"
#include "cpuid.h"
#include "simd.h"

void
simd_init(void)
{
	reg_t cr0;
	reg_t cr4;

	asm_read_cr(0, cr0);
	asm_read_cr(4, cr4);

	if (cpuid_has_sse() && cpuid_has_sse2())
	{
		cr0 &= ~((uint64_t) CR0_EMULATION);
		cr0 |= CR0_MONITOR_CO_PROCESSOR;
		cr0 |= CR0_NUMERIC_ERROR_ENABLE;

		cr4 |= CR4_FXSR_ENABLE;
		cr4 |= CR4_SIMD_EXCEPTION_SUPPORT;
	}

	if (cpuid_has_xsave())
	{
		cr4 |= CR4_XSAVE_ENABLE;
	}

	asm_write_cr(0, cr0);
	asm_write_cr(4, cr4);
}
