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

#ifndef KERNEL_TERM_H
#define KERNEL_TERM_H

#include <abstract/loader.h>
#include <stddef.h>

#define ANSI_STACK_SIZE 8

typedef enum
{
	ANSI_ESC,
	ANSI_BRACKET,
	ANSI_ATTR,
	ANSI_ENDVAL
} ansi_state_t;

typedef struct
{
	fb_t framebuffer;
	size_t cur_x;
	size_t cur_y;
	ansi_state_t state;
	size_t stack_index;
	uint32_t fg_color;
	uint32_t colors[8];

	struct
	{
		int value;
		int empty;
	} stack[ANSI_STACK_SIZE];
} term_t;

void term_init(void);
void term_puts(char const *);
void term_draw_waifu(void);

#endif /* KERNEL_TERM_H */
