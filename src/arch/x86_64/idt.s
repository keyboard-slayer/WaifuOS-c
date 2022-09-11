// Copyright (C) 2022 Keyboard Slayer
// 
// This file is part of WaifuOS.
// 
// WaifuOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// WaifuOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.



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
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rsi
    push %rdi
    push %rbp
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15
.endm

.macro __popa
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rbp
    pop %rdi
    pop %rsi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
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
        INTERRUPT_NOERR %i
    .else
        INTERRUPT_ERR %i
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
