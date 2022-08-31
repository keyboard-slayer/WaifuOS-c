#include <arch/cross-x86/gdt.h>
#include <kernel/debug.h>

void
arch_init(void)
{
	gdt_init();
}
