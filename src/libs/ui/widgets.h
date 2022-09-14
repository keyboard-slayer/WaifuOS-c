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

#ifndef UI_APP_WIDGET_H
#define UI_APP_WIDGET_H

#define UI_FONT_SIZE 12

#include <ui/utils.h>

typedef struct
{
	ui_surface_t surface;
	ui_rect_t rect;
} ui_widget_t;

void ui_widget_init(ui_widget_t *);

#endif /* UI_APP_WIDGET_H */
