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

#ifndefARCH_X86_64_LAPIC_H
#define ARCH_X86_64_LAPIC_H

#define LAPIC_CPU_ID	   0x020
#define LAPIC_EOI		   0x0b0
#define LAPIC_SPURIOUS	   0x0f0
#define LAPIC_TPR		   0x080
#define LAPIC_TIMER_REG	   0x320
#define LAPIC_INIT		   0x380
#define LAPIC_CURRENT	   0x390
#define LAPIC_TIMER_DIV	   0x3e0
#define LAPIC_ENABLE	   0x800
#define LAPIC_DIVIDE_BY_16 3

#define LAPIC_TIMER_MASK	 0x10000
#define LAPIC_TIMER_PERIODIC 0x20000

#define MSR_APICBASE 0x1B

void lapic_eoi(void);
int lapic_current_cpu(void);
void lapic_init(void);

#endif /* !ARCH_X86_64_LAPIC_H */
