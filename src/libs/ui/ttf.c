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

#include <stddef.h>
#include <stdio.h>

#include "ttf.h"

static uint32_t
read_32bits(uint8_t **buf)
{
	size_t i;
	uint32_t n = 0;
	uint8_t *m = *buf;

	for (i = 0; i < 4; i++)
	{
		n |= *m++ << (24 - (i * 8));
	}

	*buf = m;
	return n;
}

static uint16_t
read_16bits(uint8_t **buf)
{
	uint8_t *m = *buf;
	uint16_t n = *m << 8 | *(m + 1);

	m++;
	*buf = m;

	return n;
}

static void
read_offset_subtable(uint8_t **buf, offset_subtable_t *self)
{
	self->scaler_type = read_32bits(buf);
	self->num_tables = read_16bits(buf);
	self->search_range = read_16bits(buf);
	self->entry_selector = read_16bits(buf);
	self->range_shift = read_16bits(buf);
}

void
ttf_load(uint8_t *buf)
{
	offset_subtable_t off;

	read_offset_subtable(&buf, &off);

	printf("%d\n", off.num_tables);
}
