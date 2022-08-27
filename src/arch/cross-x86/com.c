#include <stdint.h>

#include "asm.h"
#include "com.h"

static int is_init = 0;

static void
write_reg(enum COM_REGS reg, uint8_t value)
{
	asm_out8(__DEBUG_SERIAL__ + reg, value);
}

static uint8_t
read_reg(enum COM_REGS reg)
{
	return asm_in8(__DEBUG_SERIAL__ + reg);
}

void
com_init(void)
{
	const uint8_t div_low = (DEFAULT_RATE / __DEBUG_SERIAL_BAUDS__) & 0xff;
	const uint8_t div_high = (DEFAULT_RATE / __DEBUG_SERIAL_BAUDS__) >> 8;

	write_reg(COM_REGS_INTERRUPT, 0x00);
	write_reg(COM_REGS_LINE_CONTROL, 0x80);
	write_reg(COM_REGS_BAUD_RATE_LOW, div_low);
	write_reg(COM_REGS_BAUD_RATE_HIGH, div_high);
	write_reg(COM_REGS_LINE_CONTROL, 0x03);
	write_reg(COM_REGS_FIFO_CONTROLLER, 0xc7);
	write_reg(COM_REGS_MODEM_CONTROL, 0x0b);

	is_init = 1;
}

void
com_putc(char c)
{
	if (!is_init)
	{
		com_init();
	}

	while ((read_reg(COM_REGS_LINE_STATUS) & 0x20) == 0)
		;

	write_reg(COM_REGS_DATA, c);
}
