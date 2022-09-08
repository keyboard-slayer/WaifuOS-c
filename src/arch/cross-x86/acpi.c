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
acpi_parse_rsdt(char const *tablename)
{
	size_t i;
	acpi_sdt_t *sdt_header = sdt;
	acpi_sdt_t *tmp;

	for (i = 0; i < sdt_header->length; i++)
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
			debug_println(DEBUG_SUCCESS, "Found %s at %p", tablename, sdt);

			if (acpi_checksum(sdt))
			{
				debug_println(DEBUG_ERROR, "Checksum failed");
				return NULL;
			}

			return sdt;
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
