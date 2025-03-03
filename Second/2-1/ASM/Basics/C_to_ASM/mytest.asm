section .data
extern var
extern var1
myA db 0x11
myB dw 0x2233
myC dq 0x44556677

section .text
global asmfunc
asmfunc:
	mov rax, 0
	mov ax, 32
	mov [var1], dword 45

	add ax, [var]  ; for return()
	ret
