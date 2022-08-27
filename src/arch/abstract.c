#include "abstract.h"

void
arch_com_puts(const char *s)
{
	while (*s)
	{
		arch_com_putc(*s++);
	}
}
