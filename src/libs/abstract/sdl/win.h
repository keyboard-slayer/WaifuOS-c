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

#ifndef LIBS_ABSTRACT_SDL_WIN_H
#define LIBS_ABSTRACT_SDL_WIN_H

typedef void *__gnuc_va_list;
typedef unsigned short wchar_t;

#include <SDL2/SDL.h>

struct ABSTRACT_WIN
{
	SDL_Window *sdl_window;
};

#endif /* LIBS_ABSTRACT_SDL_WIN_H */
