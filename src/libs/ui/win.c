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

#include <stdlib.h>
#include <string.h>

#include "win.h"

void
ui_win_init(ui_win_t *self, char const *win_name)
{
	abstract_win_init(self);

	self->widget.rect.w = 700;
	self->widget.rect.h = 500;

	self->name = malloc(strlen(win_name));
	strcpy(self->name, win_name);
}
