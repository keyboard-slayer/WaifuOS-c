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