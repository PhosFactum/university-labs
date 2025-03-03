global main

section .rodata
    msg: db "Hello, Warudo!", 10
    msglen: equ $-msg

section .text

main:
    mov rax, 1    ; write(
    mov rdi, 1
    mov rsi, msg
    mov rdx, msglen
    syscall

    mov rax, 60
    mov rdi, 0
    syscall
