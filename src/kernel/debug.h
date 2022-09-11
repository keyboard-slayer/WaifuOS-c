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

#ifndef KERNEL_DEBUG_H
#define KERNEL_DEBUG_H

#include <stdint.h>
#include <string.h>

#define __FILENAME__		  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define debug_println(L, ...) __debug_println_impl(__FILENAME__, L, __VA_ARGS__)

typedef enum
{
	DEBUG_INFO,
	DEBUG_SUCCESS,
	DEBUG_ERROR,
	DEBUG_NONE,

	DEBUG_LENGTH
} debug_level_t;

void __debug_println_impl(char const *, debug_level_t, char const *, ...);
char const *debug_retrieve_symbol(uintptr_t, size_t *);

#endif /* !KERNEL_DEBUG_H */
