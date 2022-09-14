/**
 * Copyright (C) 2022 Keyboard Slayer & contributor
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

#ifndef SRC_LIBS_UI_RECT_H
#define SRC_LIBS_UI_RECT_H

#include <stddef.h>

typedef struct
{
	size_t x;
	size_t y;
	size_t w;
	size_t h;
} ui_rect_t;

typedef struct
{
	int width;
	int height;
	int pitch;
	void *buf;
} ui_surface_t;

#endif /* SRC_LIBS_UI_RECT_H */
