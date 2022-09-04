#include <arch/abstract.h>

#include "debug.h"
#include "pmm.h"

void
bootstrap(void)
{
	pmm_init();
	arch_init();

	__asm__ volatile("int $1");

	arch_abort();
	UNREACHABLE;
}
