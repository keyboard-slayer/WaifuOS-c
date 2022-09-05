#ifndef KERNEL_TERM_H
#define KERNEL_TERM_H

#include <loader/abstract.h>
#include <stddef.h>

#define ANSI_STACK_SIZE 8

typedef enum
{
	ANSI_ESC,
	ANSI_BRACKET,
	ANSI_ATTR,
	ANSI_ENDVAL
} ansi_state_t;

typedef struct
{
	fb_t framebuffer;
	size_t cur_x;
	size_t cur_y;
	ansi_state_t state;
	size_t stack_index;
	uint32_t fg_color;
	uint32_t colors[8];

	struct
	{
		int value;
		int empty;
	} stack[ANSI_STACK_SIZE];
} term_t;

void term_init(void);
void term_puts(char const *);

#endif /* !KERNEL_TERM_H */
