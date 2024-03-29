/**
 * Copyright (C) 2022 Keyboard Slayer
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

#include <abstract/arch.h>
#include <abstract/loader.h>
#include <ctype.h>
#include <kernel/debug.h>
#include <kernel/pmm.h>
#include <macro.h>
#include <string.h>
#include <tga.h>

#include "font.h"
#include "term.h"

static int is_term_init = 0;

static term_t term = { { 0 },
					   40 + FONT_WIDTH,
					   85,
					   ANSI_ESC,
					   0,
					   0,
					   { 0, 0xF00000, 0x00F000, 0xF0F000, 0x0000F0, 0xF000F0, 0x00F0F0, 0xF0F0F0 },
					   { { 0 } } };

static void
draw_pixel(size_t x, size_t y, uint32_t color)
{
	size_t index = x + (term.framebuffer.pitch / sizeof(uint32_t)) * y;
	((uint32_t *) term.framebuffer.addr)[index] = color;
}

static void
draw_rect(size_t x, size_t y, size_t w, size_t h, uint32_t color)
{
	size_t i;
	size_t j;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			draw_pixel(x + j, y + i, color);
		}
	}
}

static void
draw_background(size_t w, size_t h)
{
	size_t x;
	size_t y;

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			draw_rect(x, y, 1, 1, 0x666699);
		}
	}
}

static void
draw_tga(void *ptr, size_t posx, size_t posy)
{
	short x;
	short y;
	tga_header_t *header = ptr;
	uint32_t *img = (uint32_t *) (sizeof(tga_header_t) + (uint64_t) header);
	size_t i = header->width * header->height;

	for (y = 0; y < header->height; y++)
	{
		for (x = header->width; x > 0; x--)
		{
			uint32_t pixel = img[i--];

			if (pixel >> 24)
			{
				draw_pixel(posx + x, posy + y, pixel);
			}
		}
	}
}

static void
print_chr(size_t xpos, size_t ypos, uint8_t c, uint32_t color)
{
	size_t x = 0;
	size_t y = 0;

	for (y = 0; y < FONT_HEIGHT; y++)
	{
		for (x = 0; x < FONT_WIDTH; x++)
		{
			if ((font[(c * FONT_HEIGHT) + y] >> x) & 1)
			{
				draw_pixel(xpos + x, ypos + y, color);
			}
		}
	}
}

static void
print_str(size_t x, size_t y, char const *s, uint32_t color)
{
	size_t cur_x = x;
	size_t cur_y = y;

	while (*s)
	{
		if (*s == '\n')
		{
			cur_y += FONT_HEIGHT;
			cur_x = 0;
		}
		else
		{
			print_chr(cur_x, cur_y, *s, color);
			cur_x += FONT_WIDTH;
		}

		s++;
	}
}

static void
term_change_fg(void)
{
	size_t i;
	int attr;
	int color;

	for (i = 0; i < term.stack_index; i++)
	{
		if (!term.stack[i].empty)
		{
			attr = term.stack[i].value;
			color = 0;

			if (attr == 0)
			{
				term.fg_color = 0;
			}
			else if (attr == 1)
			{
				color = term.stack[++i].value;
			}
			else if (attr >= 30 && attr <= 37)
			{
				color = term.stack[i].value;
				term.fg_color = term.colors[color - 30];
			}
		}
	}
}

void
term_putc(size_t x, size_t y, char c)
{
	switch (term.state)
	{
		case ANSI_ESC:
		{
			if (c == '\033')
			{
				term.state = ANSI_BRACKET;
				term.stack_index = 0;
				term.stack[term.stack_index].value = 0;
				term.stack[term.stack_index].empty = 1;
			}
			else
			{
				term.state = ANSI_ESC;
				print_chr(x, y, c, term.fg_color);
				term.cur_x += FONT_WIDTH;
			}

			break;
		}

		case ANSI_BRACKET:
		{
			if (c == '[')
			{
				term.state = ANSI_ATTR;
			}
			else
			{
				term.state = ANSI_ESC;
				print_chr(x, y, c, term.fg_color);
				term.cur_x += FONT_WIDTH;
			}

			break;
		}

		case ANSI_ATTR:
		{
			if (isdigit(c))
			{
				term.stack[term.stack_index].value *= 10;
				term.stack[term.stack_index].value += (c - '0');
				term.stack[term.stack_index].empty = 0;
				break;
			}
			else
			{
				if (term.stack_index < ANSI_STACK_SIZE)
				{
					term.stack_index++;
				}

				term.stack[term.stack_index].value = 0;
				term.stack[term.stack_index].empty = 1;

				term.state = ANSI_ENDVAL;

				FALLTHROUGH;
			}
		}

		case ANSI_ENDVAL:
		{
			switch (c)
			{
				case 'm':
				{
					term_change_fg();
					break;
				}
				case ';':
				{
					term.state = ANSI_ATTR;
					break;
				}
			}

			term.state = ANSI_ESC;
		}
	}
}

void
term_puts(char const *s)
{
	if (!is_term_init)
	{
		return;
	}

	while (*s)
	{
		if (*s == '\n')
		{
			term.cur_y += FONT_HEIGHT;
			term.cur_x = 40 + FONT_WIDTH;
			s++;
		}
		else
		{
			term_putc(term.cur_x, term.cur_y, *s++);
		}
	}
}

void
term_init(void)
{
	module_t aqua_mod;
	size_t start_x = 40;
	size_t start_y = 40;
	char const *title = "WaifuOS";

	term.framebuffer = loader_get_framebuffer();

	if (term.framebuffer.addr == 0)
	{
		debug_println(DEBUG_ERROR, "No framebuffer");
		return;
	}

	draw_background(term.framebuffer.width, term.framebuffer.height);

	/* Window shadow */
	draw_rect(start_x - 2, start_y - 1, term.framebuffer.width - 75, term.framebuffer.height - 76, 0);

	/* Window body */
	draw_rect(start_x, start_y, term.framebuffer.width - 80, term.framebuffer.height - 80, 0xffffff);

	/* Title bar */
	draw_rect(start_x + 1, start_y + 1, term.framebuffer.width - 81, 35, 0xbbbbbb);
	draw_rect(start_x, start_y + 35, term.framebuffer.width - 78, 1, 0);
	print_str(start_x + ((term.framebuffer.width - 80 - (strlen(title) * FONT_WIDTH)) / 2),
			  (35 - FONT_HEIGHT) / 2 + start_y, title, 0);

	/* Waifu */
	aqua_mod = loader_get_module("/media/aqua.tga");
	draw_tga(aqua_mod.ptr, term.framebuffer.width - 300, term.framebuffer.height - 420);

	is_term_init = 1;
}
