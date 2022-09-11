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

#ifndefKERNEL_INC_ELF_H
#define KERNEL_INC_ELF_H

#include <stdint.h>

#define ELFMAG0	   0x7F
#define ELFMAG1	   'E'
#define ELFMAG2	   'L'
#define ELFMAG3	   'F'
#define ELFCLASS64 2

typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint64_t Elf64_Xword;

enum P_TYPES
{
	PT_NULL = 0,
	PT_LOAD = 1,
	PT_DYNAMIC = 2,
	PT_INTERP = 3,
	PT_NOTE = 4,
	PT_SHLIB = 5,
	PT_PHDR = 6,
	PT_TLS = 7,
	PT_NUM = 8,
	PT_LOOS = 0x60000000,
	PT_GNU_EH_FRAME = 0x6474e550,
	PT_GNU_STACK = 0x6474e551,
	PT_GNU_RELRO = 0x6474e552,
	PT_LOSUNW = 0x6ffffffa,
	PT_SUNWBSS = 0x6ffffffa,
	PT_SUNWSTACK = 0x6ffffffb,
	PT_HISUNW = 0x6fffffff,
	PT_HIOS = 0x6fffffff,
	PT_LOPROC = 0x70000000,
	PT_HIPROC = 0x7fffffff
};

enum E_IDENT
{
	EI_MAG0 = 0,
	EI_MAG1 = 1,
	EI_MAG2 = 2,
	EI_MAG3 = 3,
	EI_CLASS = 4,
	EI_DATA = 5,
	EI_VERSION = 6,
	EI_OSABI = 7,
	EI_ABIVERSION = 8,
	EI_PAD = 9,
	EI_NIDENT = 16
};

typedef struct
{
	unsigned char e_ident[EI_NIDENT];
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
} Elf64_Ehdr;

typedef struct
{
	Elf64_Word p_type;
	Elf64_Word p_flags;
	Elf64_Off p_offset;
	Elf64_Addr p_vaddr;
	Elf64_Addr p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
} Elf64_Phdr;

typedef struct
{
	uint32_t sh_name;
	uint32_t sh_type;
	uint64_t sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	uint64_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint64_t sh_addralign;
	uint64_t sh_entsize;
} Elf64_Shdr;

typedef struct
{
	Elf64_Word st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
} Elf64_Sym;

#define ELF64_ST_BIND(info)		  ((info) >> 4)
#define ELF64_ST_TYPE(info)		  ((info) &0xf)
#define ELF64_ST_INFO(bind, type) (((bind) << 4) + ((type) &0xf))

typedef enum
{
	STT_NOTYPE = 0,
	STT_OBJECT = 1,
	STT_FUNC = 2,
	STT_SECTION = 3,
	STT_FILE = 4,
	STT_COMMON = 5,
	STT_TLS = 6,
	STT_LOOS = 10,
	STT_HIOS = 12,
	STT_LOPROC = 13,
	STT_SPARC_REGISTER = 13,
	STT_HIPROC = 15
} ELF64_ST_TYPE;

Elf64_Shdr *elf64_get_shdr(void *elf, char const *name);

#endif /* !_KERNEL_INC_ELF_H_ */
