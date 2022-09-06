#ifndef LIBC_EXT_QOI_H
#define LIBC_EXT_QOI_H

#include <macro.h>
#include <stdint.h>

typedef struct
{
	char magic[4];
	uint32_t width;
	uint32_t height;
	uint8_t channels;
	uint8_t colorspace;
} PACKED qoi_header_t;

#endif /* !LIBC_EXT_QOI_H */
