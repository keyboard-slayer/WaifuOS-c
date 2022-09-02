#include <arch/abstract.h>
#include <kernel/debug.h>

void
__interrupt_handler(void)
{
	error_println(("Int !!"));
	for (;;)
		;
}
