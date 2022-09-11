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

#ifndefARCH_CROSS_X86_ACPI_H
#define ARCH_CROSS_X86_ACPI_H

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
acpi_sdt_t *acpi_parse_sdt(char const *tablename);

#endif /* !ARCH_CROSS_X86_ACPI_H */
