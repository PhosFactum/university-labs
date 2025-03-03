section .data
    newline db 0xA ; Новая строка
    comma db ", " ; Запятая и пробел
    comma_len equ $ - comma

    file_error_msg db "File open error", 0xA
    file_error_len equ $ - file_error_msg

    input_error_msg db "Input error", 0xA
    input_error_len equ $ - input_error_msg 	

    array_full_msg db "Array is full", 0xA
    array_full_len equ $ - array_full_msg

    result_msg db "Number of negative elements satisfying the condition: ", 0
    result_msg_len equ $ - result_msg

    total_count_msg db "Total count: ", 0
    total_count_msg_len equ $ - total_count_msg

    parse_error_msg db "Parse error", 0xA
    parse_error_msg_len equ $ - parse_error_msg

    c dw -32000 ; Нижняя граница
    d dw 32000 ; Верхняя граница
    buffer_size equ 4096 ; Размер буфера

section .bss
    array resw 2000 ; Массив чисел
    n resd 305 ; Количество элементов

    buffer resb buffer_size ; Буфер
    fd resq 1 ; Файловый дескриптор

    printed_count resd 1 ; Счетчик выведенных чисел
    input_ended resb 1  ; Флаг конца ввода
    num_counter resd 1 ; Счетчик чисел

; Системные вызовы
SYS_READ equ 0
SYS_WRITE equ 1
SYS_OPEN equ 2
SYS_CLOSE equ 3
SYS_EXIT equ 60
O_RDONLY equ 0 ; Флаг: чтение

section .text
    global _start

_start:
    mov rdi, [rsp+8]        ; Количество аргументов

    ; Проверка аргументов
    cmp rdi, 2
    jl file_error

    ; Имя файла
    mov rsi, [rsp + 16]

    ; Открытие файла
    mov rax, SYS_OPEN
    mov rdi, rsi
    mov rsi, O_RDONLY
    syscall

    js file_error  ; Обработка ошибки
    mov [fd], rax   ; Сохранение дескриптора

    mov dword [n], 305   ; Инициализация n


read_loop:
    ; Чтение из файла в буфер
    mov rax, SYS_READ
    mov rdi, [fd]      ; Файловый дескриптор
    lea rsi, [buffer]  ; Адрес буфера
    mov rdx, buffer_size ; Размер буфера
    syscall

    cmp rax, 0          ; Проверка на конец файла (EOF)
    jle end_read_loop     ; Переход, если конец файла или ошибка

    lea rdi, [buffer]      ; Указатель на начало буфера
    mov r15, rax         ; Сохраняем количество прочитанных байт

parse_loop:
    cmp r14, [n]        ; Проверка на максимальное количество элементов
    jge array_bound_error

    push rdi
    push r15                ; Счетчик оставшихся байт
    call parse_int          ; Парсим число из буфера
    pop r15
    pop rdi

    jc parse_error_handler  ; Переход при ошибке парсинга

    ; Если число спаршено без ошибки
    sub r15, r8          ; Уменьшаем счетчик байт
    mov dword [array + r14*4], eax ; Сохраняем число в массив
    inc r14                 ; Увеличиваем счетчик спаршенных чисел
    add rdi, r8            ; Пропускаем обработанные символы
    inc rdi             ; Обновляем rdi


    jmp check_end_of_buffer ; Проверка на необходимость чтения новых данных

; Обработчик ошибок парсинга
parse_error_handler:
    mov rdi, r10            ; Используем сохраненное значение rdi

    ; Если конец буфера
    cmp r15, 0
    jle end_of_input_check

    ; Если не конец буфера, проверяем на запятую
    cmp byte [rdi], ','
    jne input_error        ; Если не запятая, то ошибка ввода

    ; Если запятая, пропускаем её
    inc r10              ; Пропускаем запятую
    dec r15             ; Уменьшаем количество оставшихся байтов
    mov r10, rdi         ; Перемещаем указатель
    jmp check_end_of_buffer

check_end_of_buffer:
    cmp r14, [n]
    je process_loop ; Если n чисел спаршено

    cmp r15, 0         ; Проверка на пустой буфер
    jle read_loop     ; Если буфер пуст, читаем следующую порцию

    jmp skip_separators ; Иначе продолжаем парсинг


process_array:
    jmp end_read_loop      ; Переход к обработке массива

skip_separators:
    cmp byte [rdi], ',' ; Проверка на запятую
    je next_char
    jmp parse_loop

next_char:
    inc r10              ; Пропуск запятой
    dec r15              ; Счетчик оставшихся байт
    mov rdi, r10            ; Обновляем rdi

    ; Пропуск разделителей
    cmp r15, 0             ; Проверка на конец буфера
    je read_loop          ; Если конец буфера, читаем следующую порцию
    jmp skip_separators

end_of_input_check:
    mov byte [input_ended], 1 ;
    jmp end_read_loop          ; Завершение чтения

end_read_loop:
    xor r13w, r13w      ; Индекс массива
    xor eax, eax       ; Счетчик
    mov r12w, [n]      ; Инициализируем счетчик цикла значением n
    xor dword [printed_count], 0 ; Обнуляем счетчик выведенных чисел


process_loop:
    cmp r13w, r14w       ; Сравниваем текущий индекс с количеством чисел
    jge output_result    ; Если все числа обработаны

    mov r15w, [array + r13*4] ; Загружаем текущее число

    ; Проверка на вхождение в диапазон
    mov ax, [c]          ; Нижняя граница
    cmp r15w, ax
    jl next_element      ; Если меньше нижней границы, к следующему элементу

    mov ax, [d]          ; Верхняя граница
    cmp r15w, ax
    jg next_element      ; Если больше верхней границы, к следующему элементу

    ; Если число в диапазоне, увеличиваем счетчик
    inc dword [num_counter]

print_element:
    ; Вывод числа (любого, если оно в диапазоне)
    cmp dword [printed_count], 0
    je print_number       ; Если это первое число, пропускаем запятую

    ; Вывод запятой
    mov rsi, comma
    mov rdx, comma_len
    call print_string

print_number:
    movsx rdi, r15w       ; Передаем число для вывода
    call print_int        ; Вывод числа

    inc dword [printed_count] ; Увеличиваем счетчик выведенных чисел

next_element:
    inc r13w              ; Увеличиваем индекс для следующего числа
    jmp process_loop      ; Повторяем обработку

output_result:                ; Вывод результата
    mov rdi, result_msg       ; Сообщение о результате
    mov rsi, result_msg_len   ; Длина сообщения
    call print_string

    call print_newline

    ; Вывод общего количества чисел
    mov rsi, total_count_msg
    mov rdx, total_count_msg_len
    call print_string

    mov rdi, [num_counter]
    call print_int

    call print_newline

file_error:
    mov rdi, file_error_msg
    mov rsi, file_error_len
    call print_string
    jmp exit_program

input_error:
    mov rdi, input_error_msg
    mov rsi, input_error_len
    call print_string
    jmp exit_program

parse_error:
    mov rdi, parse_error_msg
    mov rsi, parse_error_msg_len
    call print_string
    jmp exit_program

array_bound_error:
    mov rdi, array_full_msg
    mov rsi, array_full_len
    call print_string
    jmp exit_program

parse_int:
    push r9
    push rbx
    push r12
    push rdi
    push rsi

    xor eax, eax        ; Результат
    xor ebx, ebx        ; Флаг знака
    xor r12, r12        ; Счетчик цифр
    xor r9, r9          ; Спаршенное число

    ; Проверка на знак
    cmp byte [rdi], '-'
    jne .positive
    inc ebx
    inc rdi             ; Переход к следующему символу

.positive:
.parse_digit_loop:
    movzx edx, byte [rdi] ; Читаем символ
    cmp edx, '0'
    jl .check_end       ; Если не цифра, проверяем конец

    cmp edx, '9'
    jg .check_end       ; Если не цифра, проверяем конец

    ; Если цифра:
    inc r12d           ; Увеличиваем счетчик цифр
    imul r9, 10
    sub edx, '0'
    add r9d, edx       ; Добавляем цифру к числу
    inc rdi             ; Переходим к следующему символу

    jmp .parse_digit_loop

.check_end:
    ; Проверка на запятую (конец числа)
    cmp edx, ','
    je .parse_end       ; Если запятая, то конец числа
    jmp .parse_error

.parse_end:
    cmp r12d, 0       ; Проверяем, были ли прочитаны цифры
    je .parse_error

    ; Установка знака
    test ebx, ebx       ; Проверяем флаг отрицательного числа (ebx = 0, если число положительное)
    jnz .negative
    jmp .prepare_return

.negative:
    neg r9

.prepare_return:
    mov rax, rdi       ; Сохраняем текущую позицию в буфере (rdi) в rax
    pop rsi
    pop rdi
    sub rax, rdi       ; Вычисляем длину прочитанного числа (текущая позиция - начальная позиция)
    mov r8d, eax       ; Сохраняем длину в r8d (возвращаемое значение длины)
    pop r12
    pop rbx
    mov eax, r9d
    pop r9
    clc                ; Сбрасываем флаг переноса CF (нет ошибки)
    ret

.parse_error:
    xor eax, eax       ; Возвращаем 0 в eax при ошибке
    pop r9
    pop rsi
    pop rdi
    pop r12
    pop rbx
    stc                ; Устанавливаем флаг переноса CF (ошибка)
    ret


; Функция для вывода строки на экран
; rdi: адрес строки
; rsi: длина строки
print_string:
    mov rax, SYS_WRITE
    mov rdi, 1
    syscall
    ret


; Функция для вывода целого числа на экран
; rdi: число для печати
print_int:
    push rbp
    mov rbp, rsp       ; Устанавливаем rbp на вершину стека
    sub rsp, 2         ; 2 байта на стеке для буфера строки

    mov r8, 10
    mov r9, rsp        ; Указатель на буфер строки
    mov rax, rdi       ; Копируем число в rax

    test rax, rax      ; Проверяем число на знак
    jns positive_loop

    neg rax            ; Изменяем знак числа на противоположный


positive_loop:
    xor rdx, rdx
    div r8
    add dl, '0'
    mov [r9], dl       ; Записываем символ в буфер
    inc r9             ; Переходим к следующему символу в буфере
    test rax, rax
    jnz positive_loop


    ; Обработка знака после обработки цифр
    cmp rdi, 0       ; Сравниваем исходное число с 0
    jge no_sign
    mov byte [r9], '-' ; Добавляем знак минуса в буфер
    inc r9


no_sign:
    mov byte [r9], 0  ; Нуль-терминатор строки

    ; Переворачиваем строку для правильного вывода
    mov r10, rsp       ; Начало строки
    mov r11, r9        ; Конец строки
    dec r11            ; Уменьшаем r11 на 1 (исключаем нуль-терминатор)

reverse_loop:
    cmp r10, r11       ; Сравниваем начало и конец строки
    jge end_reverse

    mov al, [r10]      ; Обмен символов
    mov bl, [r11]
    mov [r10], bl
    mov [r11], al

    inc r10            ; Переходим к следующему символу
    dec r11
    jmp reverse_loop


end_reverse:
    ; Вычисляем длину строки
    mov rax, r9
    sub rax, rsp
    mov rdx, rax      ; Длина строки в rdx

    ; Выводим строку
    mov rsi, rsp
    mov rax, SYS_WRITE  ;
    mov rdi, 1
    syscall

    leave             ; Восстанавливаем rsp и rbp
    ret


; Функция для вывода новой строки
print_newline:
    mov rsi, newline
    mov rdi, 1
    mov rdx, 1
    call print_string
    ret

; Функция для завершения программы
exit_program:
    mov rax, SYS_EXIT
    xor rdi, rdi  ; Код выхода 0
    syscall
