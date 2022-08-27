#ifndef ARCH_CROSS_X86_ASM_H
#define ARCH_CROSS_X86_ASM_H

#include <stdint.h>

#define asm_hlt() __asm__("hlt")
#define asm_cli() __asm__("cli")
#define asm_sti() __asm__("sti")

void asm_out8(uint16_t port, uint8_t data);
uint8_t asm_in8(uint16_t port);

#endif /* !ARCH_CROSS_X86_ASM_H */
