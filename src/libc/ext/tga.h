#ifndef LIBC_EXT_TGA_H
#define LIBC_EXT_TGA_H

#include <macro.h>

typedef struct
{
	char idlength;
	char colourmaptype;
	char datatypecode;
	short int colourmaporigin;
	short int colourmaplength;
	char colourmapdepth;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char bitsperpixel;
	char imagedescriptor;
} PACKED tga_header_t;

typedef struct
{
	unsigned char r, g, b, a;
} rgba_t;

#endif /* !LIBC_EXT_TGA_H */
