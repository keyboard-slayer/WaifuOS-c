#ifndef KERNEL_DEBUG_H
#define KERNEL_DEBUG_H

#include <string.h>

#define __FILENAME__	   (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define info_println(x)	   __debug_println_impl(__FILENAME__, DEBUG_INFO, x)
#define success_println(x) __debug_println_impl(__FILENAME__, DEBUG_SUCCESS, x)
#define error_println(x)   __debug_println_impl(__FILENAME__, DEBUG_ERROR, x)

typedef enum
{
	DEBUG_INFO,
	DEBUG_SUCCESS,
	DEBUG_ERROR,

	DEBUG_LENGTH
} debug_level_t;

void __debug_println_impl(char const *, debug_level_t, char const *, ...);

#endif /* !KERNEL_DEBUG_H */
