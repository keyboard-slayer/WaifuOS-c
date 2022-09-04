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
