/**
 * Copyright (C) 2022 Keyboard Slayer
 *
 * This file is part of WaifuOS.
 *
 * WaifuOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WaifuOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <arch/abstract.h>
#include <loader/abstract.h>
#include <stb_sprintf.h>
#include <stdarg.h>

#include "debug.h"
#include "elf.h"
#include "macro.h"
#include "string.h"
#include "term.h"

char const *colors[DEBUG_LENGTH] = { "\033[34m", "\033[32m", "\033[31m" };

void
__debug_println_impl(char const *filename, debug_level_t level, char const *fmt, ...)
{
	char buf[512] = { 0 };
	va_list ap;

	if (level != DEBUG_NONE)
	{
		stbsp_sprintf(buf, "%s%s\033[0m ", colors[level], filename);
		term_puts(buf);
		arch_com_puts(buf);
		memset(buf, 0, 512);
	}

	va_start(ap, fmt);
	stbsp_vsprintf(buf, fmt, ap);
	arch_com_puts(buf);
	term_puts(buf);
	arch_com_putc('\n');
	term_puts("\n");
	va_end(ap);
}

char const *
debug_retrieve_symbol(uintptr_t addr, size_t *offset)
{
	int i;
	int symbol_num;
	Elf64_Shdr *symtab_sh;
	Elf64_Shdr *strtab_sh;
	Elf64_Sym *symtab;
	char const *strtab;
	uint8_t *kernel = (uint8_t *) loader_get_kfile().ptr;

	if (kernel == NULL)
	{
		debug_println(DEBUG_ERROR, "Wait... the kernel couldn't find itself");
		arch_abort();
		UNREACHABLE;
	}

	if (kernel[0] != ELFMAG0 || kernel[1] != ELFMAG1 || kernel[2] != ELFMAG2 || kernel[3] != ELFMAG3)
	{
		debug_println(DEBUG_ERROR, "Wait... the kernel is not an elf. WHAT HAVE YOU DONE !?");
		arch_abort();
		UNREACHABLE;
	}

	symtab_sh = elf64_get_shdr(kernel, ".symtab");
	strtab_sh = elf64_get_shdr(kernel, ".strtab");

	if (symtab_sh == NULL || strtab_sh == NULL)
	{
		debug_println(DEBUG_ERROR, "Couldn't get required sections");
		arch_abort();
		UNREACHABLE;
	}

	symbol_num = symtab_sh->sh_size / symtab_sh->sh_entsize;
	symtab = (void *) ((uintptr_t) kernel + (uintptr_t) symtab_sh->sh_offset);
	strtab = (void *) ((uintptr_t) kernel + (uintptr_t) strtab_sh->sh_offset);

	for (i = 0; i < symbol_num; i++)
	{
		if (symtab[i].st_name && addr > symtab[i].st_value && addr < symtab[i].st_value + symtab[i].st_size &&
			ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC)
		{
			*offset = addr - symtab[i].st_value;
			return strtab + symtab[i].st_name;
		}
	}

	return NULL;
}
