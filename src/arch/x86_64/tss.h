#ifndef ARCH_X86_64_TSS_H
#define ARCH_X86_64_TSS_H

#include <stdint.h>

typedef struct PACKED
{
	uint32_t reserved;
	uint64_t rsp[3];
	uint64_t reserved0;
	uint64_t ist[7];

	uint32_t reserved1;
	uint32_t reserved2;
	uint16_t reserved3;

	uint16_t iopb_offset;
} __attribute__((packed)) tss_t;

typedef struct
{
	uint16_t length;
	uint16_t base_low16;
	uint8_t base_mid8;
	uint8_t flags1;
	uint8_t flags2;
	uint8_t base_high8;
	uint32_t base_upper32;
	uint32_t reserved;
} __attribute__((packed)) tss_entry_t;

#endif /* !ARCH_X86_64_TSS_H */
