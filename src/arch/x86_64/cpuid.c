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
	return (cpuid(CPUID_FEATURE_IDENTIFIER, 0).edx & CPUID_EXFEATURE_PDPE1GB);
}
