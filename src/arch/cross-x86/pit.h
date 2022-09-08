#ifndef ARCH_CROSS_X86_PIT_H
#define ARCH_CROSS_X86_PIT_H

#include <stdint.h>

void pit_init(void);
void pit_sleep(uint16_t);
void pit_set_reload_value(uint16_t);

#endif /* !ARCH_CROSS_X86_PIT_H */
