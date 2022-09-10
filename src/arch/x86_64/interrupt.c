#include <arch/abstract.h>
#include <kernel/debug.h>
#include <kernel/term.h>
#include <stdint.h>

#include "lapic.h"
#include "macro.h"

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
	size_t offset;
	char const *symbol = debug_retrieve_symbol(regs->rip, &offset);

	__asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
	__asm__ volatile("mov %%cr2, %0" : "=r"(cr2));
	__asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
	__asm__ volatile("mov %%cr4, %0" : "=r"(cr4));

	arch_com_putc('\n');
	term_puts("\n");
	debug_println(DEBUG_ERROR, "Exception %s (0x%x) Err: %d", exception_messages[regs->intno], regs->intno, regs->err);
	debug_println(DEBUG_NONE, "RAX %p RBX %p RCX %p RDX %p", regs->rax, regs->rbx, regs->rcx, regs->rdx);
	debug_println(DEBUG_NONE, "RSI %p RDI %p RBP %p RSP %p", regs->rsi, regs->rdi, regs->rbp, regs->rsp);
	debug_println(DEBUG_NONE, "R8  %p R9  %p R10 %p R11 %p", regs->r8, regs->r9, regs->r10, regs->r11);
	debug_println(DEBUG_NONE, "R12 %p R13 %p R14 %p R15 %p", regs->r12, regs->r13, regs->r14, regs->r15);
	debug_println(DEBUG_NONE, "CR0 %p CR2 %p CR3 %p CR4 %p", cr0, cr2, cr3, cr4);
	debug_println(DEBUG_NONE, "CS  %p SS  %p FLG %p", regs->cs, regs->ss, regs->rflags);
	debug_println(DEBUG_NONE, "RIP \033[7m%p\033[0m <%s+0x%lx>", regs->rip, symbol, offset);
}

static void
print_traceback(reg_t rbp)
{
	uintptr_t *old_bp;
	uintptr_t *ret_addr;
	size_t offset;
	char const *symbol;
	uintptr_t *base_ptr = (uintptr_t *) rbp;

	if (base_ptr == NULL)
	{
		return;
	}

	debug_println(DEBUG_NONE, "\nTraceback:");

	for (;;)
	{
		old_bp = (uintptr_t *) base_ptr[0];
		ret_addr = (uintptr_t *) base_ptr[1];
		symbol = debug_retrieve_symbol((uintptr_t) ret_addr, &offset);

		if (ret_addr == NULL || old_bp == NULL)
		{
			break;
		}

		debug_println(DEBUG_NONE, "  [%p] <%s+0x%lx>", (uintptr_t) ret_addr, symbol, offset);
		base_ptr = old_bp;
	}
}

static void
irq_handler(regs_t *regs)
{
	switch (regs->intno)
	{
		case IRQ(0):
		{
			break;
		}
	}
}

uintptr_t
__interrupt_handler(reg_t rsp)
{
	regs_t *regs = (regs_t *) rsp;

	if (regs->intno < IRQ(0))
	{
		output_exception(regs);
		print_traceback(regs->rbp);
		arch_abort();
		UNREACHABLE;
	}
	else if (regs->intno <= IRQ(15))
	{
		irq_handler(regs);
	}

	lapic_eoi();
	return rsp;
}
