#ifndef ARCH_CROSS_X86_RSDP_H
#define ARCH_CROSS_X86_RSDP_H

#include <macro.h>
#include <stdint.h>

typedef struct
{
	char signature[8];
	uint8_t checksum;
	char oemid[6];
	uint8_t revision;
	uint32_t rsdtAddress;
	uint32_t length;
	uint64_t xsdt_addr;
	uint8_t ext_checksum;
	char reserved[3];
} PACKED rsdp_t;

typedef struct
{
	char signature[4];
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oemid[6];
	char oemtableid[8];
	uint32_t oemrevision;
	uint32_t creatorid;
	uint32_t creatorrevision;
} PACKED acpi_sdt_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

typedef struct
{
	acpi_sdt_t header;
	uint32_t sdtAddr[];
} PACKED rsdt_t;

typedef struct
{
	acpi_sdt_t header;
	uint64_t sdtAddr[];
} PACKED xsdt_t;

#pragma GCC diagnostic pop

void acpi_init(void);

int acpi_checksum(acpi_sdt_t *table);
acpi_sdt_t *acpi_parse_rsdt(char const *tablename);

#endif /* !ARCH_CROSS_X86_RSDP_H */
