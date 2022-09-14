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

#ifndef LIBS_UI_TTF_H
#define LIBS_UI_TTF_H

#define TRUETYPE_SCALER_TYPE			0x74727565
#define OPENTYPE_POSTSCRIPT_SCALER_TYPE 0x4F54544F
#define POSTSCRIPT1_SCALER_TYPE			0x74797031

#include <stdint.h>

typedef struct
{
	uint32_t scaler_type;
	uint16_t num_tables;
	uint16_t search_range;
	uint16_t entry_selector;
	uint16_t range_shift;
} offset_subtable_t;

typedef struct
{
	uint32_t tag;
	uint32_t checksum;
	uint32_t offset;
	uint32_t length;
} table_dir_t;

typedef struct
{
	offset_subtable_t off_sub;
	table_dir_t *table_dir;
} font_directory_t;

#endif /* LIBS_UI_TTF_H */
