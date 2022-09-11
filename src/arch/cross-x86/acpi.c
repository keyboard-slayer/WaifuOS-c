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

#include <arch/abstract.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <macro.h>
#include <stddef.h>
#include <string.h>

#include "acpi.h"

static void *sdt;
static int xsdt = 0;

void
acpi_init(void)
{
	rsdp_t *rsdp = (rsdp_t *) loader_get_rsdp();
	if (rsdp == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't get RSDP");
		arch_abort();
		UNREACHABLE;
	}

	if (rsdp->revision >= 2 && rsdp->xsdt_addr != 0)
	{
		debug_println(DEBUG_INFO, "Using XSDT");
		xsdt = 1;
		sdt = (void *) ((uintptr_t) rsdp->xsdt_addr + loader_get_hhdm());
	}
	else
	{
		debug_println(DEBUG_INFO, "Using Rsdt");
		sdt = (void *) ((uintptr_t) rsdp->rsdtAddress + loader_get_hhdm());
	}
}

acpi_sdt_t *
acpi_parse_sdt(char const *tablename)
{
	size_t i;
	acpi_sdt_t *tmp;
	acpi_sdt_t *sdt_header = sdt;
	size_t entry_count = (sdt_header->length - sizeof(acpi_sdt_t)) / (xsdt ? sizeof(uint64_t) : sizeof(uint32_t));

	for (i = 0; i < entry_count; i++)
	{
		if (xsdt)
		{
			tmp = (acpi_sdt_t *) (((xsdt_t *) sdt)->sdtAddr[i] + loader_get_hhdm());
		}
		else
		{
			tmp = (acpi_sdt_t *) (((rsdt_t *) sdt)->sdtAddr[i] + loader_get_hhdm());
		}

		if (memcmp(tablename, tmp->signature, 4) == 0)
		{
			debug_println(DEBUG_INFO, "Found %s at %p", tablename, tmp);

			if (acpi_checksum(tmp))
			{
				debug_println(DEBUG_ERROR, "Checksum failed");
				return NULL;
			}

			return tmp;
		}
	}

	return NULL;
}

int
acpi_checksum(acpi_sdt_t *table)
{
	size_t i;
	unsigned char sum = 0;

	for (i = 0; i < table->length; i++)
	{
		sum += ((char *) table)[i];
	}

	return sum;
}
