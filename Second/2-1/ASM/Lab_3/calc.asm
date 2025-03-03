section .data
extern ss_a, ss_b, ss_d, us_a, us_b, us_d, numerator, denominator, quotient

global signed
global unsigned
global zero_div

section .text

zero_div:
    xor eax, eax             ; Обнуляем результат в случае деления на ноль
    ret

; signed int
signed:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; 2 * d - 96 / a
    mov eax, [ss_d]
    shl eax, 1               ; умножение на 2
    mov ebx, eax             ; сохраняем 2 * d

    mov ecx, [ss_a]
    mov eax, 96
    cdq                       ; расширение знака для деления
    test ecx, ecx
    jz zero_div               ; проверка деления на ноль
    idiv ecx                  ; 96 / a
    mov edx, eax

    sub ebx, edx              ; числитель = 2 * d - 96 / a
    mov [numerator], ebx

    ; 34 / b - a + 1
    mov ecx, [ss_b]
    mov eax, 34
    cdq                       ; расширение знака для деления
    test ecx, ecx
    jz zero_div               ; проверка деления на ноль
    idiv ecx                  ; 34 / b
    mov ebx, eax

    sub ebx, ecx
    add ebx, 1                ; знаменатель = 34 / b - a + 1
    mov [denominator], ebx

    ; Числитель / Знаменатель
    mov eax, [numerator]
    cdq
    mov ebx, [denominator]
    test ebx, ebx
    jz zero_div
    idiv ebx                  ; результат = числитель / знаменатель
    mov [quotient], eax

    ret

; unsigned int
unsigned:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; 2 * d - 96 / a
    mov eax, [us_d]
    shl eax, 1               ; умножение на 2
    mov ebx, eax             ; сохраняем 2 * d

    mov ecx, [us_a]
    mov eax, 96
    test ecx, ecx
    jz zero_div               ; проверка деления на ноль
    div ecx                   ; 96 / a
    mov edx, eax

    sub ebx, edx              ; числитель = 2 * d - 96 / a
    mov [numerator], ebx

    ; 34 / b - a + 1
    mov ecx, [us_b]
    mov eax, 34
    test ecx, ecx
    jz zero_div               ; проверка деления на ноль
    div ecx                   ; 34 / b
    mov ebx, eax

    sub ebx, ecx
    add ebx, 1                ; знаменатель = 34 / b - a + 1
    mov [denominator], ebx

    ; Числитель / Знаменатель
    mov eax, [numerator]
    mov ebx, [denominator]
    test ebx, ebx
    jz zero_div
    div ebx                   ; результат = числитель / знаменатель
    mov [quotient], eax

    ret

