#include <bits/stdint-uintn.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <macro.h>

#include "font.h"
#include "term.h"

static fb_t fb;

static void
draw_pixel_fb(fb_t *self, size_t x, size_t y, uint32_t color)
{
	size_t index = x + (self->pitch / sizeof(uint32_t)) * y;
	((uint32_t *) self->addr)[index] = color;
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
			draw_pixel_fb(&fb, x + j, y + i, color);
		}
	}
}

static void
draw_background(size_t w, size_t h)
{
	size_t x;
	size_t y;
	uint32_t color = 0xffffff;

	for (y = 0; y < h; y += 2)
	{
		color = color == 0 ? 0xffffff : 0;
		for (x = 0; x < w; x += 2)
		{
			draw_rect(x, y, 1, 1, color);
			color = color == 0 ? 0xffffff : 0;
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
			if ((font[((c - ' ') * FONT_HEIGHT) + y] >> x) & 1)
			{
				draw_pixel_fb(&fb, xpos + x, ypos + y, color);
			}
		}
	}
}

USED static void
print_str(size_t x, size_t y, char const *s, uint32_t color)
{
	size_t cur_x = x;
	size_t cur_y = y;

	debug_println(DEBUG_NONE, "OK");

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

void
term_init(void)
{
	size_t start_x = 40;
	size_t start_y = 40;

	fb = loader_get_framebuffer();

	if (fb.addr == 0)
	{
		debug_println(DEBUG_ERROR, "No framebuffer");
		return;
	}

	draw_background(fb.width, fb.height);

	/* Window shadow */
	draw_rect(start_x - 2, start_y - 2, fb.width - 75, fb.height - 75, 0);

	/* Window body */
	draw_rect(start_x, start_y, fb.width - 80, fb.height - 80, 0xffffff);

	/* Window title bar */
	draw_rect(start_x, start_y, fb.width - 80, 35, 0xefefef);
	draw_rect(start_x, start_y, fb.width - 80, 1, 0xb5b3dd);
	draw_rect(start_x, start_y + 1, fb.width - 80, 1, 0xd3d3ff);
	draw_rect(start_x, start_y, 1, 35, 0xb5b3dd);
	draw_rect(start_x + 1, start_y, 1, 35, 0xd3d3ff);
	draw_rect(fb.width - 40, start_y, 1, 35, 0xb5b3dd);
	draw_rect(fb.width - 41, start_y, 1, 35, 0xd3d3ff);
	draw_rect(start_x, start_y + 34, fb.width - 80, 1, 0xb5b3dd);
	draw_rect(start_x, start_y + 33, fb.width - 80, 1, 0xb5b3dd);
	draw_rect(start_x, start_y + 35, fb.width - 80, 3, 0);
}