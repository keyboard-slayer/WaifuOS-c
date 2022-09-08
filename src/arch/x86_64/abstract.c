#include <arch/cross-x86/acpi.h>
#include <arch/cross-x86/asm.h>
#include <arch/cross-x86/gdt.h>
#include <arch/cross-x86/idt.h>
#include <arch/cross-x86/pit.h>
#include <kernel/debug.h>

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
	lapic_init();

	debug_println(DEBUG_SUCCESS, "Arch initialised");
}
