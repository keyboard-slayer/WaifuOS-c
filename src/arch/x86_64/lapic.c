#include <arch/abstract.h>
#include <arch/cross-x86/pit.h>
#include <kernel/debug.h>
#include <loader/abstract.h>
#include <stddef.h>

#include "asm.h"
#include "lapic.h"
#include "macro.h"

static uintptr_t lapic_addr;

static uint32_t
lapic_read(uint32_t reg)
{
	return *((volatile uint32_t *) (lapic_addr + reg));
}

static void
lapic_write(uint32_t reg, uint32_t value)
{
	*((volatile uint32_t *) (lapic_addr + reg)) = value;
}

void
lapic_timer_init(void)
{
	uint32_t ticks;

	lapic_write(LAPIC_TPR, 0);

	lapic_write(LAPIC_TIMER_DIV, LAPIC_DIVIDE_BY_16);
	lapic_write(LAPIC_INIT, 0xffffffff);

	pit_sleep(10);

	lapic_write(LAPIC_TIMER_REG, LAPIC_TIMER_MASK);

	ticks = 0xffffffff - lapic_read(LAPIC_CURRENT);

	lapic_write(LAPIC_TIMER_REG, IRQ(0) | LAPIC_TIMER_PERIODIC);
	lapic_write(LAPIC_TIMER_DIV, LAPIC_DIVIDE_BY_16);
	lapic_write(LAPIC_INIT, ticks);
}

void
lapic_eoi(void)
{
	lapic_write(LAPIC_EOI, 0);
}

int
lapic_current_cpu(void)
{
	if (lapic_addr == 0)
	{
		return 0;
	}

	return lapic_read(LAPIC_CPU_ID) >> 24;
}

void
lapic_init(void)
{
	lapic_addr = (asm_read_msr(MSR_APICBASE) & 0xfffff000) + loader_get_hhdm();
	asm_write_msr(MSR_APICBASE, (asm_read_msr(MSR_APICBASE) | LAPIC_ENABLE) & ~((1 << 10)));
	lapic_write(LAPIC_SPURIOUS, lapic_read(LAPIC_SPURIOUS) | 0x1ff);

	lapic_timer_init();
}
