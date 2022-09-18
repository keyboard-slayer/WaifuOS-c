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

#include <abstract/posix/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonts.h"
#include "ttf.h"

void
ui_load_font(char const *filepath)
{
	uint8_t *buf = posix_file_read(filepath);

	if (memcmp(buf, "\x00\x01\x00\x00\x00", 5) == 0 || memcmp(buf, "\x4f\x54\x54\x4f", 5) == 0)
	{
		ttf_load(buf);
	}

	free((void *) buf);
}
