#include <arch/abstract.h>
#include <arch/cross-x86/acpi.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <stddef.h>

#include "ioapic.h"
#include "macro.h"

static void
ioapic_write(madt_ioapic_t *io_apic, uint32_t reg, uint32_t value)
{
	uint64_t base = (uint64_t) io_apic->ioapic_addr + loader_get_hhdm();
	*(volatile uint32_t *) base = reg;
	*(volatile uint32_t *) (base + 16) = value;
}

static void
ioapic_set_gsi_redirect(uint32_t lapic_id, uint8_t intno, uint8_t gsi, uint16_t flags)
{
	uint32_t io_redirect_table;
	ioapic_redirect_t redirect = { 0 };
	madt_ioapic_t *ioapic = madt_get_ioapic_from_gsi(gsi);
	if (ioapic == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't get IOAPIC from GSI");
		arch_abort();
		UNREACHABLE;
	}

	redirect._redirect.vector = intno;

	if (flags & IOAPIC_ACTIVE_HIGH_LOW)
	{
		redirect._redirect.polarity = 1;
	}

	if (flags & IOAPIC_TRIGGER_EDGE_LOW)
	{
		redirect._redirect.trigger = 1;
	}

	redirect._redirect.dest_id = lapic_id;

	io_redirect_table = (gsi - ioapic->gsib) * 2 + 16;
	ioapic_write(ioapic, io_redirect_table, (uint32_t) redirect._raw.low_byte);
	ioapic_write(ioapic, io_redirect_table + 1, (uint32_t) redirect._raw.high_byte);
}

void
ioapic_redirect_irq(uint32_t lapic_id, uint8_t intno, uint8_t irq)
{
	madt_iso_t *iso = madt_get_iso_irq(irq);
	if (iso != NULL)
	{
		ioapic_set_gsi_redirect(lapic_id, intno, iso->gsi, iso->flags);
	}
	else
	{
		ioapic_set_gsi_redirect(lapic_id, intno, irq, 0);
	}
}

void
ioapic_init(void)
{
	size_t i;

	for (i = 0; i < 16; i++)
	{
		ioapic_redirect_irq(0, IRQ(i), i);
	}
}
