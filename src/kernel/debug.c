#include <arch/abstract.h>
#include <loader/abstract.h>
#include <stb_sprintf.h>
#include <stdarg.h>

#include "debug.h"
#include "elf.h"
#include "string.h"

char const *colors[DEBUG_LENGTH] = { "\033[34m", "\033[32m", "\033[31m" };

void
__debug_println_impl(char const *filename, debug_level_t level, char const *fmt, ...)
{
	char buf[512] = { 0 };
	va_list ap;

	if (level != DEBUG_NONE)
	{
		arch_com_puts(colors[level]);
		arch_com_puts(filename);
		arch_com_puts("\033[0m");
		arch_com_putc(' ');
	}

	va_start(ap, fmt);
	stbsp_vsprintf(buf, fmt, ap);
	arch_com_puts(buf);
	arch_com_putc('\n');
	va_end(ap);
}

#pragma message("TODO")
void
debug_retrieve_symbol(uintptr_t addr)
{
	(void) addr;
	uint8_t *kernel = (uint8_t *) loader_get_kfile();

	if (kernel == NULL)
	{
		debug_println(DEBUG_ERROR, "Wait... the kernel couldn't find itself");
		arch_abort();
	}

	if (kernel[0] != ELFMAG0 || kernel[1] != ELFMAG1 || kernel[2] != ELFMAG2 || kernel[3] != ELFMAG3)
	{
		debug_println(DEBUG_ERROR, "Wait... the kernel is not an elf. WHAT HAVE YOU DONE !?");
		arch_abort();
	}
}
