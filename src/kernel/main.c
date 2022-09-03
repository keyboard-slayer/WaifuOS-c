#include <arch/abstract.h>

#include "debug.h"
#include "pmm.h"

void
bootstrap(void)
{
	pmm_init();
	arch_init();
	arch_abort();

	UNREACHABLE;
}
