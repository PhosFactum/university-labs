section .text
global main

main:
    mov  eax, 10
    cdq
    mov  ecx, 3
    div  ecx
    int  80h
