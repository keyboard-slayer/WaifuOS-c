/**
 * Copyright (C) 2022 Keyboard Slayer
 *
 * This file is part of waifuOS.
 *
 * waifuOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * waifuOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with waifuOS.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBS_ABSTRACT_ARCH_H
#define LIBS_ABSTRACT_ARCH_H

#include <macro.h>

#ifdef __x86_64__
# include <arch/cross-x86/const.h>
# include <arch/x86_64/regs.h>
#else
# error "Unknown architecture"
#endif /* __x86_64__ */

NORETURN void arch_abort(void);
void arch_com_putc(char);
void arch_com_puts(char const *);
void arch_init(void);

#endif /* LIBS_ABSTRACT_ARCH_H */
