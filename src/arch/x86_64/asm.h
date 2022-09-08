#ifndef ARCH_X86_64_ASM_H
#define ARCH_X86_64_ASM_H

#include <arch/cross-x86/asm.h>

void asm_write_msr(uint64_t msr, uint64_t value);
uint64_t asm_read_msr(uint64_t msr);

#endif /* !ARCH_X86_64_ASM_H */
