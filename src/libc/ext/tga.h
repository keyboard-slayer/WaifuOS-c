#ifndef LIBC_EXT_TGA_H
#define LIBC_EXT_TGA_H

#include <stdint.h>

typedef struct
{
	uint8_t magic1;
	uint8_t colormap;
	uint8_t encoding;
	uint16_t cmaporig;
	uint16_t cmaplen;
	uint8_t cmapent;
	uint16_t x;
	uint16_t y;
	uint16_t h;
	uint16_t w;
	uint8_t bpp;
} __attribute__((packed)) tga_header_t;

#endif /* !LIBC_EXT_TGA_H */
