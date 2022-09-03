#include <arch/abstract.h>
#include <kernel/debug.h>

void
__interrupt_handler(void)
{
	debug_println(DEBUG_ERROR, "Int !!");
	for (;;)
		;
}
