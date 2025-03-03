section .data

extern var_init
extern var_asm

section .text
global asmfunc
asmfunc:
    mov rax, 0
    mov ax, 4
    mov [var_asm], dword 12

    add ax, [var_init]
    ret
