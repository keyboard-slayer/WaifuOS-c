#ifndef ARCH_ABSTRACT_H
#define ARCH_ABSTRACT_H

void arch_abort(void);
void arch_com_putc(char);
void arch_com_puts(char const *);
void arch_init(void);

#endif /* !ARCH_ABSTRACT_H */
