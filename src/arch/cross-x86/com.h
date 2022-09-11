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

#ifndef ARCH_CROSS_X86_COM_H
#define ARCH_CROSS_X86_COM_H

#include <stdint.h>

#ifndef __DEBUG_SERIAL__
# error "no serial port specified"
#endif /* !__DEBUG_SERIAL__ */

#define DEFAULT_RATE (115200)

enum COM_REGS
{
	COM_REGS_DATA = 0,
	COM_REGS_INTERRUPT = 1,
	COM_REGS_BAUD_RATE_LOW = 0,
	COM_REGS_BAUD_RATE_HIGH = 1,
	COM_REGS_INTERRUPT_IDENTIFICATOR = 2,
	COM_REGS_FIFO_CONTROLLER = 2,
	COM_REGS_LINE_CONTROL = 3,
	COM_REGS_MODEM_CONTROL = 4,
	COM_REGS_LINE_STATUS = 5,
	COM_REGS_MODEM_STATUS = 6,
	COM_REGS_SCRATCH_REGISTER = 7
};

void com_putc(char);
void com_puts(char const *);

#endif /* !ARCH_CROSS_X86_COM_H */
