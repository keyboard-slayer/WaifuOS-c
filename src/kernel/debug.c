#include <arch/abstract.h>
#include <stb_sprintf.h>
#include <stdarg.h>

#include "debug.h"

char const *colors[DEBUG_LENGTH] = { "\033[34m", "\033[32m", "\033[31m" };

void
__debug_println_impl(char const *filename, debug_level_t level, char const *fmt, ...)
{
	char buf[512] = { 0 };
	va_list ap;

	arch_com_puts(colors[level]);
	arch_com_puts(filename);
	arch_com_puts("\033[0m");
	arch_com_putc(' ');

	va_start(ap, fmt);
	stbsp_vsprintf(buf, fmt, ap);
	arch_com_puts(buf);
	arch_com_putc('\n');
	va_end(ap);
}
