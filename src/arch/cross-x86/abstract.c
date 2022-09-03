#include <arch/abstract.h>

#include "asm.h"
#include "com.h"
#include "macro.h"

NORETURN void
arch_abort(void)
{
	for (;;)
	{
		asm_cli();
		asm_hlt();
	}

	UNREACHABLE;
}

void
arch_com_putc(char c)
{
	com_putc(c);
}
