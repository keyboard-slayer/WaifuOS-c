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

#include "cpuid.h"

cpuid_result_t
cpuid(uint32_t leaf, uint32_t subleaf)
{
	uint32_t cpuid_max;
	cpuid_result_t result;

	/* clang-format off */
    __asm__ volatile(
        "cpuid"
        : "=a" (cpuid_max)
        : "a" (leaf & 0x80000000)
        : "ebx", "ecx", "edx"
    );
	/* clang-format on */

	if (leaf > cpuid_max)
	{
		result.succ = 0;
		return result;
	}

	result.succ = 1;

	/* clang-format off */
    __asm__ volatile(
        "cpuid"
        : "=a" (result.eax), "=b" (result.ebx), "=c" (result.ecx), "=d" (result.edx)
        : "a" (leaf), "c" (subleaf)
    );
	/* clang-format on */

	return result;
}

int
cpuid_has_1gb_page(void)
{
	return (cpuid(CPUID_EXTENDED_LEAF, 0).edx & CPUID_EXFEATURE_PDPE1GB);
}

int
cpuid_has_sse(void)
{
	return (cpuid(CPUID_FEATURE_IDENTIFIER, 0).edx & CPUID_SSE_SUPPORT);
}

int
cpuid_has_sse2(void)
{
	return (cpuid(CPUID_FEATURE_IDENTIFIER, 0).edx & CPUID_SSE2_SUPPORT);
}

int
cpuid_has_xsave(void)
{
	return (cpuid(CPUID_FEATURE_IDENTIFIER, 0).ecx & CPUID_XSAVE_SUPPORT) == CPUID_XSAVE_SUPPORT;
}
