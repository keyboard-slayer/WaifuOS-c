#include "macro.h"
#include <arch/abstract.h>
#include <kernel/debug.h>
#include <stdint.h>

static char *exception_messages[32] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Detected Overflow",
	"Out Of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad Tss",
	"Segment Not Present",
	"StackFault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Security Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
};

static void
output_exception(regs_t const *regs)
{
	uint64_t cr0;
	uint64_t cr2;
	uint64_t cr3;
	uint64_t cr4;

	__asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
	__asm__ volatile("mov %%cr2, %0" : "=r"(cr2));
	__asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
	__asm__ volatile("mov %%cr4, %0" : "=r"(cr4));

	arch_com_putc('\n');
	debug_println(DEBUG_ERROR, "Exception %s (0x%x) Err: %d", exception_messages[regs->intno], regs->intno, regs->err);
	debug_println(DEBUG_NONE, "RAX %p RBX %p RCX %p RDX %p", regs->rax, regs->rbx, regs->rcx, regs->rdx);
	debug_println(DEBUG_NONE, "RSI %p RDI %p RBP %p RSP %p", regs->rsi, regs->rdi, regs->rbp, regs->rsp);
	debug_println(DEBUG_NONE, "R8  %p R9  %p R10 %p R11 %p", regs->r8, regs->r9, regs->r10, regs->r11);
	debug_println(DEBUG_NONE, "R12 %p R13 %p R14 %p R15 %p", regs->r12, regs->r13, regs->r14, regs->r15);
	debug_println(DEBUG_NONE, "CR0 %p CR2 %p CR3 %p CR4 %p", cr0, cr2, cr3, cr4);
	debug_println(DEBUG_NONE, "CS  %p SS  %p FLG %p", regs->cs, regs->ss, regs->rflags);
	debug_println(DEBUG_NONE, "RIP \033[7m%p\033[0m (%s)", regs->rip, debug_retrieve_symbol(regs->rip));
}

uintptr_t
__interrupt_handler(reg_t rsp)
{
	regs_t *regs = (regs_t *) rsp;

	if (regs->intno < 32)
	{
		output_exception(regs);
		arch_abort();
		UNREACHABLE;
	}

	return rsp;
}
