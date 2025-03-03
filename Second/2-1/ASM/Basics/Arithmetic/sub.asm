section .data

section .text
global main

main:
    mov  eax, 3
    mov  ebx, 5
    sub  eax, ebx
    mov  ebx, 2
    add  eax, ebx
    int  80h
