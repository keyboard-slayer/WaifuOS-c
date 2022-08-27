#include <arch/abstract.h>

void
bootstrap(void)
{
	arch_com_puts("Hello, World !");
	arch_abort();
}
