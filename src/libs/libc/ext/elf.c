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

#include <kernel/debug.h>
#include <stddef.h>
#include <string.h>

#include "elf.h"

Elf64_Shdr *
elf64_get_shdr(void *elf, char const *name)
{
	size_t i;
	Elf64_Ehdr *header = (Elf64_Ehdr *) elf;
	Elf64_Shdr *shdr = (Elf64_Shdr *) ((uintptr_t) elf + header->e_shoff);
	Elf64_Shdr *strtab = (Elf64_Shdr *) &shdr[header->e_shstrndx];
	char const *sh_strtab_p = (char const *) ((uintptr_t) elf + strtab->sh_offset);

	if (name == NULL)
	{
		return shdr;
	}

	for (i = 0; i < header->e_shnum; i++)
	{
		if (strcmp(name, sh_strtab_p + shdr[i].sh_name) == 0)
		{
			return &shdr[i];
		}
	}

	return NULL;
}
