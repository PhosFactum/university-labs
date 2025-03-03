; calc_signed.asm

; (b+a)/(a-1) , если a > b
; 23 , если a = b
; b*b/8 , если a < b


section .data
    extern a_signed
    extern b_signed
    extern X_signed

section .text
    global calculate_expression_signed

calculate_expression_signed:
    mov eax, [a_signed]
    mov ebx, [b_signed]

    ; Преобразуем значения в 64-битные регистры
    movsxd rax, eax
    movsxd rbx, ebx

    cmp rax, rbx
    jg case_a_greater_b
    je case_a_equal_b
    jl case_a_less_b

case_a_greater_b:
    ; (b + a) / (a - 1)
    mov rcx, rax      ; rcx = a
    add rbx, rcx      ; rbx = b + a
    dec rcx           ; rcx = a - 1 (делитель)
    test rcx, rcx     ; проверка деления на 0
    je divide_by_zero
    mov rax, rbx      ; перемещаем (b + a) в rax для деления
    cqo               ; расширяем rax для знакового деления
    idiv rcx          ; rax = (b + a) / (a - 1)
    mov [X_signed], rax
    ret

case_a_equal_b:
    mov rax, 23
    mov [X_signed], rax
    ret

case_a_less_b:
    ; b * b / 8
    mov rax, rbx
    imul rax, rbx     ; rax = b * b
    mov rcx, 8
    cqo               ; расширяем rax для знакового деления
    idiv rcx          ; rax = (b * b) / 8
    mov [X_signed], rax
    ret

divide_by_zero:
    mov rax, 0
    mov [X_signed], rax
    ret

