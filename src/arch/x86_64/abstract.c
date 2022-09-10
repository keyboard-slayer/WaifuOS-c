#include <arch/cross-x86/acpi.h>
#include <arch/cross-x86/asm.h>
#include <arch/cross-x86/gdt.h>
#include <arch/cross-x86/idt.h>
#include <arch/cross-x86/madt.h>
#include <arch/cross-x86/pit.h>
#include <kernel/debug.h>

#include "ioapic.h"
#include "lapic.h"
#include "vmm.h"

void
arch_init(void)
{
	gdt_init();
	idt_init();
	vmm_init();
	pit_init();
	acpi_init();
	madt_init();
	lapic_init();
	ioapic_init();
	asm_sti();

	__asm__("int $0x20");

	debug_println(DEBUG_SUCCESS, "Arch initialised");
}
