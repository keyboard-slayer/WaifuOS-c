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

#include "pit.h"
#include "asm.h"

uint32_t
pit_read_count(void)
{
	uint32_t counter;

	asm_out8(0x43, 0);
	counter = asm_in8(0x40);
	counter |= asm_in8(0x40) << 8;

	return counter;
}

void
pit_init(void)
{
	int divisor = 1193180 / 100;

	asm_out8(0x43, 0x36);
	asm_out8(0x40, divisor & 0xff);
	asm_out8(0x40, (divisor >> 8) & 0xFF);
}

void
pit_sleep(uint16_t ms)
{
	asm_out8(0x43, 0x30);
	asm_out8(0x40, ms & 0xff);
	asm_out8(0x40, (ms >> 8) & 0xff);

	while (pit_read_count() == 0)
		;
}
