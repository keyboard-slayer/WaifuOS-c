#include <arch/abstract.h>

#include "debug.h"
#include "macro.h"
#include "pmm.h"
#include "term.h"

void
bootstrap(void)
{
	term_init();
	pmm_init();
	arch_init();

	for (;;)
		;
	UNREACHABLE;
}
