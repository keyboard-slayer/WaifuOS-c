#include <arch/abstract.h>

#include "debug.h"
#include "pmm.h"
#include "term.h"

void
bootstrap(void)
{
	term_init();
	pmm_init();
	arch_init();

	__asm__ volatile("int $1");

	arch_abort();
	UNREACHABLE;
}
