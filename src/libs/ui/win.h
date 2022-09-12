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

#ifndef LIBS_UI_WIN_H
#define LIBS_UI_WIN_H

#include <abstract/win.h>

#include "widgets.h"

typedef struct UI_WIN
{
	ui_widget_t widget;
	abstract_win_t abstract;
	char const *name;

	void (*push)(struct UI_WIN *, ui_widget_t);
	void (*refresh)(struct UI_WIN *);
} ui_win_t;

typedef void (*ui_method_t)(ui_win_t *);
void ui_win_init(ui_win_t *, char const *);

#endif /* LIBS_UI_WIN_H */
