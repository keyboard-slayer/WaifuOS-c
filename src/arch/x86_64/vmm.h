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

#ifndefARCH_X86_64_VMM_H
#define ARCH_X86_64_VMM_H

/* PAGING HELL IS REAL */

#include <macro.h>
#include <mem.h>
#include <stddef.h>
#include <stdint.h>

#define PMLX_GET_INDEX(addr, level) (((uint64_t) addr & ((uint64_t) 0x1ff << (12 + level * 9))) >> (12 + level * 9))
#define VMM_PRESENT					((uint64_t) 1 << (uint64_t) 0)
#define VMM_WRITABLE				((uint64_t) 1 << (uint64_t) 1)
#define VMM_USER					((uint64_t) 1 << (uint64_t) 2)
#define VMM_HUGE					((uint64_t) 1 << (uint64_t) 7)
#define VMM_NOEXE					((uint64_t) 1 << (uint64_t) 63)
#define VMM_GET_ADDR(x)				((x) &0x000ffffffffff000)

void vmm_init(void);

#endif /* !ARCH_X86_64_VMM_H */
