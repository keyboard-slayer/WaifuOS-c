#ifndef ARCH_X86_64_IOAPIC_H
#define ARCH_X86_64_IOAPIC_H

#include <arch/cross-x86/madt.h>
#include <stdint.h>

#define IOAPIC_ACTIVE_HIGH_LOW	(1 << 1)
#define IOAPIC_TRIGGER_EDGE_LOW (1 << 3)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
typedef union PACKED
{
	struct
	{
		uint8_t vector;
		uint8_t delivery_mode : 3;
		uint8_t dest_mode : 1;
		uint8_t delivery_status : 1;
		uint8_t polarity : 1;
		uint8_t remote_irr : 1;
		uint8_t trigger : 1;
		uint8_t mask : 1;
		uint8_t reserved : 7;
		uint8_t dest_id;
	} PACKED _redirect;

	struct
	{
		uint32_t low_byte;
		uint32_t high_byte;
	} PACKED _raw;
} ioapic_redirect_t;
#pragma GCC diagnostic pop

void ioapic_redirect_irq(uint32_t, uint8_t, uint8_t);
void ioapic_init(void);

#endif /* !ARCH_X86_64_IOAPIC_H */
