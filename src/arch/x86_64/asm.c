#include "asm.h"

void
asm_write_msr(uint64_t msr, uint64_t value)
{
	uint32_t low = value & 0xFFFFFFFF;
	uint32_t high = value >> 32;
	__asm__ volatile("wrmsr" ::"c"((uint64_t) msr), "a"(low), "d"(high));
}

uint64_t
asm_read_msr(uint64_t msr)
{
	uint32_t low, high;
	__asm__ volatile("rdmsr" : "=a"(low), "=d"(high) : "c"((uint64_t) msr));
	return ((uint64_t) high << 32) | low;
}
