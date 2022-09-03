#ifndef KERNEL_DEBUG_H
#define KERNEL_DEBUG_H

#include <string.h>

#define __FILENAME__		  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define debug_println(L, ...) __debug_println_impl(__FILENAME__, L, __VA_ARGS__)

typedef enum
{
	DEBUG_INFO,
	DEBUG_SUCCESS,
	DEBUG_ERROR,

	DEBUG_LENGTH
} debug_level_t;

void __debug_println_impl(char const *, debug_level_t, char const *, ...);

#endif /* !KERNEL_DEBUG_H */
