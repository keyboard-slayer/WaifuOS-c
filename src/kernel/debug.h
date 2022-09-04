#ifndef KERNEL_DEBUG_H
#define KERNEL_DEBUG_H

#include <stdint.h>
#include <string.h>

#define __FILENAME__		  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define debug_println(L, ...) __debug_println_impl(__FILENAME__, L, __VA_ARGS__)

typedef enum
{
	DEBUG_INFO,
	DEBUG_SUCCESS,
	DEBUG_ERROR,
	DEBUG_NONE,

	DEBUG_LENGTH
} debug_level_t;

void __debug_println_impl(char const *, debug_level_t, char const *, ...);
char const *debug_retrieve_symbol(uintptr_t);

#endif /* !KERNEL_DEBUG_H */
