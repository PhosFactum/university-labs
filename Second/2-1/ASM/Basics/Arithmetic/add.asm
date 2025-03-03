section .data

section .text
global main

main:
    mov  al, 0b11111111
    mov  bl, 0b0001
    add  al, bl  ; sum (add)
    adc  ah, 0   ; sum (add with carry)

    int 80h
