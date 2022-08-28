.globl gdt_flush

gdt_flush:
    lgdt (%rdi)

    mov $0x10, %ax
    mov %ax, %ss
    mov %ax, %ds
    mov %ax, %es
    movq $trampoline, %rax

    pushq %rax
    retq

    trampoline:
        ret
