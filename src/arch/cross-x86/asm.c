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

#include "asm.h"

void
asm_out8(uint16_t port, uint8_t data)
{
	__asm__ volatile("outb %0, %1" : : "a"(data), "d"(port));
}

uint8_t
asm_in8(uint16_t port)
{
	uint8_t data;
	__asm__ volatile("inb %1, %0" : "=a"(data) : "d"(port));
	return data;
}

uint64_t
asm_read_xcr(uint32_t i)
{
	uint32_t eax;
	uint32_t edx;
	__asm__ volatile("xgetbv" : "=a"(eax), "=d"(edx) : "c"(i) : "memory");

	return eax | ((uint64_t) edx << 32);
}

void
asm_write_xcr(uint32_t i, uint64_t value)
{
	uint32_t edx = value >> 32;
	uint32_t eax = (uint32_t) value;

	__asm__ volatile("xsetbv" : : "a"(eax), "d"(edx), "c"(i) : "memory");
}
