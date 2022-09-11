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

#ifndef ARCH_CROSS_X86_CPUID_H
#define ARCH_CROSS_X86_CPUID_H

#include <stdbool.h>
#include <stdint.h>

#define CPUID_EXTENDED_LEAF		 0x80000001
#define CPUID_FEATURE_IDENTIFIER 0x1

typedef struct
{
	uint8_t succ;
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
} cpuid_result_t;

enum cpuid_extended_feature_bits
{
	CPUID_EXFEATURE_PDPE1GB = 1 << 26
};

enum cpuid_feature_bits
{
	CPUID_SSE_SUPPORT = 1 << 25,
	CPUID_SSE2_SUPPORT = 1 << 26,
	CPUID_XSAVE_SUPPORT = 1 << 26

};

cpuid_result_t cpuid(uint32_t leaf, uint32_t subleaf);

int cpuid_has_1gb_page(void);
int cpuid_has_sse(void);
int cpuid_has_sse2(void);
int cpuid_has_xsave(void);

#endif /* !ARCH_CROSS_X86_CPUID_H */
