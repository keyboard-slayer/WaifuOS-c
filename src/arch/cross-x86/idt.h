#ifndef ARCH_CROSS_X86_IDT_H
#define ARCH_CROSS_X86_IDT_H

#define IDT_LENGTH 256

#include <macro.h>
#include <stdint.h>

typedef struct
{
	uint16_t limit;
	uint64_t base;
} PACKED idt_descriptor_t;

typedef struct
{
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t zero;
} PACKED idt_entry_t;

typedef enum
{
	INT_TASK_GATE = 0x5,
	INT_INTERRUPT_GATE = 0xE,
	INT_TRAP_GATE = 0xF,
	INT_PRESENT = 1 << 7
} interrupt_type_t;

extern uintptr_t __interrupts_vector[];
extern void idt_flush(uintptr_t);
void idt_init(void);

#endif /* !ARCH_CROSS_X86_IDT_H */
