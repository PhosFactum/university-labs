; calc_unsigned.asm

; (b+a)/(a-1) , если a > b
; 23 , если a = b
; b*b/8 , если a < b

section .data
    extern a_unsigned
    extern b_unsigned
    extern X_unsigned

section .text
    global calculate_expression_unsigned

calculate_expression_unsigned:
    mov eax, [a_unsigned]
    mov ebx, [b_unsigned]

    ; Преобразуем значения в 64-битные регистры
    mov rax, rax    ; rax = a_unsigned
    mov rbx, rbx    ; rbx = b_unsigned

    cmp rax, rbx
    ja case_a_greater_b
    je case_a_equal_b
    jb case_a_less_b

case_a_greater_b:
    ; (b + a) / (a - 1)
    mov rcx, rax      ; rcx = a
    add rbx, rcx      ; rbx = b + a
    dec rax           ; rax = a - 1
    test rax, rax     ; проверка деления на 0
    je divide_by_zero
    mov rdx, 0        ; для div используем беззнаковое деление
    div rax           ; rbx = (b + a) / (a - 1)
    mov [X_unsigned], rbx
    ret

case_a_equal_b:
    mov rax, 23
    mov [X_unsigned], rax
    ret

case_a_less_b:
    ; b * b / 8
    mov rax, rbx
    mul rbx           ; rax = b * b
    mov rcx, 8
    div rcx           ; rax = (b * b) / 8
    mov [X_unsigned], rax
    ret

divide_by_zero:
    mov rax, 0
    mov [X_unsigned], rax
    ret

