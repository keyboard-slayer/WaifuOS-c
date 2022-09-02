#include <kernel/debug.h>

#include "asm.h"
#include "gdt.h"
#include "idt.h"

static idt_entry_t idt_entries[IDT_LENGTH] = { 0 };
static idt_descriptor_t idt = { 0 };

static void
idt_init_entry(idt_entry_t *self, uint64_t base, interrupt_type_t type)
{
	self->offset_low = base & 0xFFFF;
	self->offset_mid = (base >> 16) & 0xFFFF;
	self->offset_high = (base >> 32) & 0xFFFFFFFF;

	self->ist = 0;
	self->selector = GDT_KERNEL_CODE * 8;
	self->type_attr = INT_PRESENT | type;
	self->zero = 0;
}

void
idt_init(void)
{
	int i;
	for (i = 0; i < 48; i++)
	{
		idt_init_entry(&idt_entries[i], __interrupts_vector[i], INT_TRAP_GATE);
	}

	idt.base = (uintptr_t) &idt_entries[0];
	idt.limit = sizeof(idt_entries) - 1;
	idt_flush((uint64_t) &idt);

	success_println(("Loaded"));
}
