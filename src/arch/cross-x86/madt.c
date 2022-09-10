#include <arch/abstract.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <stddef.h>

#include "acpi.h"
#include "madt.h"

static uint32_t lapic_addr = 0;
static madt_t *madt;

void
madt_init(void)
{
	madt = (madt_t *) acpi_parse_sdt("APIC");
	if (madt == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't get MADT");
		arch_abort();
		UNREACHABLE;
	}

	lapic_addr = madt->lapic_addr;
}

static uint32_t
io_apic_read(madt_ioapic_t *ioapic, uint32_t reg)
{
	uintptr_t base = (uintptr_t) ioapic->ioapic_addr + loader_get_hhdm();
	*(volatile uint32_t *) (base) = reg;
	return *(volatile uint32_t *) (base + 0x10);
}

static size_t
ioapic_gsi_count(madt_ioapic_t *ioapic)
{
	uint32_t val = io_apic_read(ioapic, 1);
	ioapic_version_t *ver = (ioapic_version_t *) &val;
	return ver->max_redirect;
}

madt_ioapic_t *
madt_get_ioapic_from_gsi(uint32_t gsi)
{
	size_t i = 0;
	madt_entry_t *entry;
	while (i < madt->header.length - sizeof(madt_t))
	{
		entry = (madt_entry_t *) (madt->entries + i);

		if (entry->type == 1)
		{
			madt_ioapic_t *ioapic = (madt_ioapic_t *) entry;

			if (gsi >= ioapic->gsib && gsi < ioapic->gsib + ioapic_gsi_count(ioapic))
			{
				return ioapic;
			}
		}

		i += MAX(2, entry->length);
	}

	return NULL;
}

madt_iso_t *
madt_get_iso_irq(uint8_t irq)
{
	size_t i = 0;
	while (i < madt->header.length - sizeof(madt_t))
	{
		madt_entry_t *entry = (madt_entry_t *) madt->entries + i;

		if (entry->type == 2)
		{
			madt_iso_t *iso = (madt_iso_t *) entry;
			if (iso->irq_src == irq)
			{
				return iso;
			}
		}

		i += MAX(2, entry->length);
	}

	return NULL;
}

uint32_t
madt_get_lapic_addr()
{
	return lapic_addr;
}
