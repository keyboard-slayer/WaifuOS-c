#include <arch/abstract.h>

void
bootstrap(void)
{
	arch_init();
	arch_com_puts("Hello, World !\n");
	arch_abort();
}
