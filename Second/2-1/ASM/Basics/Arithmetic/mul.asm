section .data

section .text
global main

main:
    mov  al, 100
    mov  bl, 2
    mul  bl
    int 80h
