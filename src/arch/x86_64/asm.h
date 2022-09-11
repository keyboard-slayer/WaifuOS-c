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

#ifndef ARCH_X86_64_ASM_H
#define ARCH_X86_64_ASM_H

#include <arch/abstract.h>
#include <arch/cross-x86/asm.h>

void asm_write_msr(uint64_t msr, uint64_t value);
uint64_t asm_read_msr(uint64_t msr);

#endif /* !ARCH_X86_64_ASM_H */
