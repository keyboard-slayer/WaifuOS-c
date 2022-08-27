#include <arch/abstract.h>

#include "asm.h"
#include "com.h"

void
arch_abort(void)
{
	for (;;)
	{
		asm_cli();
		asm_hlt();
	}
}

void
arch_com_putc(char c)
{
	com_putc(c);
}
