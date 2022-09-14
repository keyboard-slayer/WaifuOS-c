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

/* clang-format off */
#include <ui/win.h>
#include <SDL2/SDL_video.h>
/* clang-format on */

void
abstract_win_init(ui_win_t *self)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	self->abstract.sdl_window = SDL_CreateWindow(
		self->name,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		self->widget.rect.h,
		self->widget.rect.w,
		SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI);

	if (self->abstract.sdl_window == NULL)
	{
		fprintf(stderr, "%s", SDL_GetError());
		exit(1);
	}
}
