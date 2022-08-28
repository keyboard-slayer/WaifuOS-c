#include <arch/cross-x86/gdt.h>

void
arch_init(void)
{
	gdt_init();
}
