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

#ifndefARCH_CROSS_X86_ASM_H
#define ARCH_CROSS_X86_ASM_H

#include <arch/abstract.h>
#include <stdint.h>

#define asm_hlt() __asm__("hlt")
#define asm_cli() __asm__("cli")
#define asm_sti() __asm__("sti")

#define asm_read_cr(n, reg) __asm__ volatile("mov %%cr" #n ", %0" : "=r"(reg))
#define asm_write_cr(n, x)	__asm__ volatile("mov %0, %%cr" #n ::"r"((x)))

void asm_out8(uint16_t port, uint8_t data);
uint8_t asm_in8(uint16_t port);
void asm_write_xcr(uint32_t i, uint64_t value);
uint64_t asm_read_xcr(uint32_t i);

enum cr0_bit
{
	CR0_PROTECTED_MODE_ENABLE = (1 << 0),
	CR0_MONITOR_CO_PROCESSOR = (1 << 1),
	CR0_EMULATION = (1 << 2),
	CR0_TASK_SWITCHED = (1 << 3),
	CR0_EXTENSION_TYPE = (1 << 4),
	CR0_NUMERIC_ERROR_ENABLE = (1 << 5),
	CR0_WRITE_PROTECT_ENABLE = (1 << 16),
	CR0_ALIGNMENT_MASK = (1 << 18),
	CR0_NOT_WRITE_THROUGH_ENABLE = (1 << 29),
	CR0_CACHE_DISABLE = (1 << 30),
	CR0_PAGING_ENABLE = (1 << 31)
};

enum cr4_bit
{
	CR4_VIRTUAL_8086_MODE_EXT = (1 << 0),
	CR4_PROTECTED_MODE_VIRTUAL_INT = (1 << 1),
	CR4_TIME_STAMP_DISABLE = (1 << 2),
	CR4_DEBUGGING_EXT = (1 << 3),
	CR4_PAGE_SIZE_EXT = (1 << 4),
	CR4_PHYSICAL_ADDRESS_EXT = (1 << 5),
	CR4_MACHINE_CHECK_EXCEPTION = (1 << 6),
	CR4_PAGE_GLOBAL_ENABLE = (1 << 7),
	CR4_PERFORMANCE_COUNTER_ENABLE = (1 << 8),
	CR4_FXSR_ENABLE = (1 << 9),
	CR4_SIMD_EXCEPTION_SUPPORT = (1 << 10),
	CR4_USER_MODE_INSTRUCTION_PREVENTION = (1 << 11),
	CR4_5_LEVEL_PAGING_ENABLE = (1 << 12),
	CR4_VIRTUAL_MACHINE_EXT_ENABLE = (1 << 13),
	CR4_SAFER_MODE_EXT_ENABLE = (1 << 14),
	CR4_FS_GS_BASE_ENABLE = (1 << 16),
	CR4_PCID_ENABLE = (1 << 17),
	CR4_XSAVE_ENABLE = (1 << 18),
	CR4_SUPERVISOR_EXE_PROTECTION_ENABLE = (1 << 20),
	CR4_SUPERVISOR_ACCESS_PROTECTION_ENABLE = (1 << 21),
	CR4_KEY_PROTECTION_ENABLE = (1 << 22),
	CR4_CONTROL_FLOW_ENABLE = (1 << 23),
	CR4_SUPERVISOR_KEY_PROTECTION_ENABLE = (1 << 24)
};

enum xcr0_bit
{
	XCR0_XSAVE_SAVE_X87 = (1 << 0),
	XCR0_XSAVE_SAVE_SSE = (1 << 1),
	XCR0_AVX_ENABLE = (1 << 2),
	XCR0_BNDREG_ENABLE = (1 << 3),
	XCR0_BNDCSR_ENABLE = (1 << 4),
	XCR0_AVX512_ENABLE = (1 << 5),
	XCR0_ZMM0_15_ENABLE = (1 << 6),
	XCR0_ZMM16_32_ENABLE = (1 << 7),
	XCR0_PKRU_ENABLE = (1 << 9)
};

#endif /* !ARCH_CROSS_X86_ASM_H */
