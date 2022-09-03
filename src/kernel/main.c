#include <arch/abstract.h>

#include "debug.h"

void
bootstrap(void)
{
	arch_init();
	arch_abort();

	UNREACHABLE;
}
