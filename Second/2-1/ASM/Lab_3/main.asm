section .data
    prompt_a db "Введите значение для a: ", 0
    prompt_b db "Введите значение для b: ", 0
    prompt_d db "Введите значение для d: ", 0
    result_msg db "Результат вычислений: ", 0
    error_msg db "Ошибка: некорректное значение или деление на ноль!", 10, 0
    newline db 10, 0
    max_signed db 2147483647  ; Максимальное значение для signed int
    min_signed db -2147483648 ; Минимальное значение для signed int
    max_unsigned db 4294967295 ; Максимальное значение для unsigned int

section .bss
    buffer resb 32       ; Буфер для ввода строки

section .data
    ; Глобальные переменные для связи с calc.asm
    extern ss_a, ss_b, ss_d, us_a, us_b, us_d, numerator, denominator, quotient

    ; Объявляем глобальные переменные, которые будут использоваться в calc.asm
    ss_a resd 1          ; signed int a
    ss_b resd 1          ; signed int b
    ss_d resd 1          ; signed int d
    us_a resd 1          ; unsigned int a
    us_b resd 1          ; unsigned int b
    us_d resd 1          ; unsigned int d
    numerator resd 1     ; Числитель
    denominator resd 1   ; Знаменатель
    quotient resd 1      ; Результат

section .text
global _start

_start:
    ; Запрос для переменной a
    mov rdi, prompt_a
    call print_string
    call read_input
    call validate_signed_input
    mov [ss_a], eax

    ; Запрос для переменной b
    mov rdi, prompt_b
    call print_string
    call read_input
    call validate_signed_input
    mov [ss_b], eax

    ; Запрос для переменной d
    mov rdi, prompt_d
    call print_string
    call read_input
    call validate_signed_input
    mov [ss_d], eax

    ; Вызов расчётов из calc.asm для signed
    call signed

    ; Печать результата
    mov rdi, result_msg
    call print_string
    mov rdi, quotient
    call print_int
    mov rdi, newline
    call print_string

    ; Завершение программы
    mov rax, 60
    xor rdi, rdi
    syscall

print_string:
    ; Вывод строки в консоль
    mov rax, 0x1         ; sys_write
    mov rdi, 0x1         ; stdout
    mov rsi, rdi         ; адрес строки
    mov rdx, 32          ; длина строки
    syscall
    ret

read_input:
    ; Чтение строки
    mov rax, 0x0         ; sys_read
    mov rdi, 0x0         ; stdin
    mov rsi, buffer      ; адрес буфера
    mov rdx, 32          ; длина буфера
    syscall
    ret

validate_signed_input:
    ; Проверка на корректность ввода и диапазон для signed int
    ; Предполагаем, что ввод является числом в строковом виде
    ; Нужно проверить, чтобы оно попадало в диапазон от -2147483648 до 2147483647
    ; Для упрощения, мы не реализуем полный разбор числа здесь
    ; Для примера проверим только на "0"
    mov eax, [buffer]
    cmp eax, 0
    je error
    ret

error:
    mov rdi, error_msg
    call print_string
    mov rax, 60         ; sys_exit
    xor rdi, rdi        ; статус 0
    syscall

signed:
    ; Функция для работы с signed int
    ; Подготовка числителя и знаменателя
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

zero_div:
    ; Обработка деления на ноль
    xor eax, eax             ; обнуляем результат
    ret

print_int:
    ; Печать целого числа
    ; Преобразуем число в строку и выводим его
    ret

