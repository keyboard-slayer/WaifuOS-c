.altmacro
.globl idt_flush
.globl __interrupts_vector
.extern __interrupt_handler

.macro INTERRUPT_NAME intno
    .quad __interrupt\intno
.endm

.macro INTERRUPT_ERR intno
__interrupt\intno:
    pushq $\intno
    jmp __interrupt_common
.endm

.macro INTERRUPT_NOERR intno
__interrupt\intno:
    pushq $0
    pushq $\intno
    jmp __interrupt_common
.endm

.macro __pusha
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
.endm

.macro __popa
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax
.endm

__interrupt_common:
    cld
    __pusha

    movq %rsp, %rdi
    call __interrupt_handler
    movq %rax, %rsp

    __popa
    add $16, %rsp
    iretq

.set i,0
.rept 48
    .if i != 8 && i != 10 && i != 11 && i != 12 && i != 13 && i != 14 && i != 17 && i != 30
        INTERRUPT_ERR %i
    .else
        INTERRUPT_NOERR %i
    .endif 
    .set i,i+1
.endr

.align 8
__interrupts_vector:
.set i,0
.rept 48
    INTERRUPT_NAME %i
    .set i,i+1
.endr

idt_flush:
    lidt (%rdi)
    ret
