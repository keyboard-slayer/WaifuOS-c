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

#ifndef LIBS_LIBC_ABSTRACT_WIN_H
#define LIBS_LIBC_ABSTRACT_WIN_H

#ifdef __HOST__
# include <abstract/sdl/win.h>
#endif /* __HOST__ */

typedef struct ABSTRACT_WIN abstract_win_t;
typedef struct UI_WIN ui_win_t;

void abstract_win_init(ui_win_t *);

#endif /* LIBS_LIBC_ABSTRACT_WIN_H */
