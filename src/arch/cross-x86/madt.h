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

#ifndef ARCH_CROSS_X86_MADT_H
#define ARCH_CROSS_X86_MADT_H

#include <macro.h>
#include <stddef.h>
#include <stdint.h>

#include "acpi.h"

typedef struct
{
	uint8_t type;
	uint8_t length;
} PACKED madt_entry_t;

typedef struct
{
	madt_entry_t header;
	uint8_t bus_src;
	uint8_t irq_src;
	uint32_t gsi;
	uint16_t flags;
} PACKED madt_iso_t;

typedef struct
{
	madt_entry_t header;
	uint8_t ioapic_id;
	uint8_t _reserved;
	uint32_t ioapic_addr;
	uint32_t gsib;
} PACKED madt_ioapic_t;

typedef struct
{
	uint8_t version;
	uint8_t reserved;
	uint8_t max_redirect;
	uint8_t reserved2;
} PACKED ioapic_version_t;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

typedef struct
{
	acpi_sdt_t header;
	uint32_t lapic_addr;
	uint32_t flags;
	uint8_t entries[];
} PACKED madt_t;

#pragma GCC diagnostic pop

void madt_init(void);
uint32_t madt_get_lapic_addr(void);
madt_iso_t *madt_get_iso_irq(uint8_t irq);
madt_ioapic_t *madt_get_ioapic_from_gsi(uint32_t gsi);

#endif /* ARCH_CROSS_X86_MADT_H */
