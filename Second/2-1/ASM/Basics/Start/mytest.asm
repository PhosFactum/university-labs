extern printf

section .data

msg: db "Hello, world!", 0x0a
len: db $-msg

msg1: db "Hello, World with (syscall)!", 0x0a
len1: db $-msg1

msg2: db "Hello, World with (printf)!", 0x0a, 0
fmt: db "%s", 0


section .text

global main
main:
; for 32-bit
	mov eax, 4
	mov ebx, 1
	mov ecx, msg
	movzx edx, byte [len]
	int 0x80

; for 64-bit 
	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	movzx rdx, byte [len1]
	syscall

; output with a 'printf'
	push rbx
	mov rdi, fmt
	mov rsi, msg2
	mov rax, 0
	call printf
	pop rbx

; exiting the ASM-program
    mov eax, 1
	mov ebx, 0
	int 80h
	
