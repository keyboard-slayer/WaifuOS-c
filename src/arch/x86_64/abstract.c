#include <arch/cross-x86/asm.h>
#include <arch/cross-x86/gdt.h>
#include <arch/cross-x86/idt.h>
#include <kernel/debug.h>

void
arch_init(void)
{
	gdt_init();
	idt_init();
	asm_sti();

	__asm__ volatile("int $1");
}
