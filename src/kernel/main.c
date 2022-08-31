#include <arch/abstract.h>

void
bootstrap(void)
{
	arch_init();
	arch_abort();
}
