.globl gdt_flush

gdt_flush:
    lgdt (%rdi)
    
    mov $0x10, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    pop %rdi

    mov $0x08, %rax
    push %rax
    push %rdi
    retfq