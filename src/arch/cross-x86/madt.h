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

#endif /* !ARCH_CROSS_X86_MADT_H */
