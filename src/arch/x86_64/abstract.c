#include <arch/cross-x86/asm.h>
#include <arch/cross-x86/gdt.h>
#include <arch/cross-x86/idt.h>
#include <arch/x86_64/vmm.h>
#include <kernel/debug.h>

void
arch_init(void)
{
	gdt_init();
	idt_init();
	/* 	vmm_init(); */
	asm_sti();
}
