#ifndef ARCH_X86_64_CPUID_H
#define ARCH_X86_64_CPUID_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	uint8_t succ;
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
} cpuid_result_t;

enum cpuid_leaf
{
	CPUID_FEATURE_IDENTIFIER = 1,
	CPUID_EXTENDED_FEATURE_IDENTIFIER = 7,
	CPUID_PROC_EXTENDED_STATE_ENUMERATION = 13
};

enum cpuid_extended_feature_bits
{
	CPUID_EXFEATURE_PDPE1GB = 1 << 26
};

cpuid_result_t cpuid(uint32_t leaf, uint32_t subleaf);

int cpuid_has_1gb_page(void);

#endif /* !ARCH_X86_64_CPUID_H */
