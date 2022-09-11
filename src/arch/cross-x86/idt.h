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

#ifndef ARCH_CROSS_X86_IDT_H
#define ARCH_CROSS_X86_IDT_H

#define IDT_LENGTH 256

#include <macro.h>
#include <stdint.h>

typedef struct
{
	uint16_t limit;
	uint64_t base;
} PACKED idt_descriptor_t;

typedef struct
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
} PACKED idt_entry_t;

typedef enum
{
	INT_TASK_GATE = 0x5,
	INT_INTERRUPT_GATE = 0xE,
	INT_TRAP_GATE = 0xF,
	INT_PRESENT = 1 << 7
} interrupt_type_t;

extern uintptr_t __interrupts_vector[];
extern void idt_flush(uintptr_t);
void idt_init(void);

#endif /* !ARCH_CROSS_X86_IDT_H */
