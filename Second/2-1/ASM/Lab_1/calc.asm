; calc.asm
;
; Выражение имеет следующий вид:
; (2 * d - 96 / a) / (34 / b - a + 1)

extern sca, scb, scd, scRes, scNum, scDen
extern ssa, ssb, ssd, ssRes, ssNum, ssDen
extern uca, ucb, ucd, ucRes, ucNum, ucDen
extern usa, usb, usd, usRes, usNum, usDen

global asm_sc
global asm_ss
global asm_uc
global asm_us

section .text

zero_div:
    xor eax, eax         ; обнуляем результат
    ret

; signed char (8-bit: -128 to 127)
asm_sc:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; 2 * d - 96 / a
    movsx eax, byte [scd]
    shl eax, 1
    mov ebx, eax

    movsx ecx, byte [sca]
    mov eax, 96
    cdq
    test ecx, ecx
    jz zero_div
    idiv ecx
    mov edx, eax

    sub ebx, edx            ; числитель = 2 * d - 96 / a
    mov [scNum], ebx

    ; 34 / b - a + 1
    movsx ecx, byte [scb]
    mov eax, 34
    cdq
    test ecx, ecx
    jz zero_div
    idiv ecx
    mov ebx, eax

    movsx eax, byte [sca]
    sub ebx, eax
    add ebx, 1              ; знаменатель = 34 / b - a + 1
    mov [scDen], ebx

    ; Числитель / Знаменатель
    mov eax, [scNum]
    cdq
    mov ebx, [scDen]
    test ebx, ebx
    jz zero_div
    idiv ebx                 ; результат = числитель / знаменатель
    mov [scRes], eax

    ret

; signed integer (16-bit: -32768 to 32767)
asm_ss:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; 2 * d - 96 / a
    movsx eax, word [ssd]
    shl eax, 1
    mov ebx, eax

    movsx ecx, word [ssa]
    mov eax, 96
    cdq
    test ecx, ecx
    jz zero_div
    idiv ecx
    mov edx, eax

    sub ebx, edx           ; числитель = 2 * d - 96 / a
    mov [ssNum], ebx

    ; 34 / b - a + 1
    movsx ecx, word [ssb]
    mov eax, 34
    cdq
    test ecx, ecx
    jz zero_div
    idiv ecx
    mov ebx, eax

    movsx eax, word [ssa]
    sub ebx, eax
    add ebx, 1            ; знаменатель = 34 / b - a + 1
    mov [ssDen], ebx

    ; Числитель / Знаменатель
    mov eax, [ssNum]
    cdq
    mov ebx, [ssDen]
    test ebx, ebx
    jz zero_div
    idiv ebx               ; результат = числитель / знаменатель
    mov [ssRes], eax

    ret

; unsigned char (8-bit: 0 to 255)
asm_uc:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; 2 * d - 96 / a
    movzx eax, byte [ucd]   ; загружаем d (8-битный unsigned)
    shl eax, 1              ; 2 * d
    mov ebx, eax            ; сохраняем числитель

    movzx ecx, byte [uca]   ; загружаем a (8-битный unsigned)
    mov eax, 96
    xor edx, edx            ; очищаем edx перед делением
    test ecx, ecx           ; проверяем деление на 0
    jz zero_div
    div ecx                 ; 96 / a
    mov edx, eax            ; сохраняем результат деления

    sub ebx, edx            ; числитель = 2 * d - (96 / a)
    mov [ucNum], ebx        ; сохраняем числитель

    ; 34 / b - a + 1
    movzx ecx, byte [ucb]   ; загружаем b (8-битный unsigned)
    mov eax, 34
    xor edx, edx            ; очищаем edx перед делением
    test ecx, ecx           ; проверяем деление на 0
    jz zero_div
    div ecx                 ; 34 / b
    mov ebx, eax            ; сохраняем результат

    movzx eax, byte [uca]   ; загружаем a (8-битный unsigned)
    sub ebx, eax            ; знаменатель = (34 / b) - a
    add ebx, 1              ; знаменатель = (34 / b) - a + 1
    mov [ucDen], ebx        ; сохраняем знаменатель

    ; Числитель / Знаменатель
    movzx eax, byte [ucNum]        ; загружаем числитель
    xor edx, edx            ; очищаем edx перед делением

    ; Теперь используем movzx для загрузки беззнакового значения из ucDen
    movzx ebx, byte [ucDen] ; загружаем знаменатель как unsigned 8-битное значение
    test ebx, ebx           ; проверяем деление на 0
    jz zero_div
    div ebx                 ; результат = числитель / знаменатель
    mov [ucRes], eax        ; сохраняем результат

    ret


; unsigned integer (16-bit: 0 to 65535)
asm_us:
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; Числитель: 2 * d - (96 / a)
    movzx eax, word [usd]     ; загружаем d (16-битный unsigned)
    shl eax, 1                ; 2 * d
    mov ebx, eax              ; сохраняем числитель

    movzx ecx, word [usa]     ; загружаем a (16-битный unsigned)
    mov eax, 96
    xor edx, edx              ; очищаем edx перед делением
    test ecx, ecx             ; проверяем деление на 0
    jz zero_div
    div ecx                   ; 96 / a
    sub ebx, eax              ; числитель = 2 * d - (96 / a)
    mov [usNum], ebx          ; сохраняем числитель

    ; Знаменатель: (34 / b) - a + 1
    movzx ecx, word [usb]     ; загружаем b (16-битный unsigned)
    mov eax, 34
    xor edx, edx              ; очищаем edx перед делением
    test ecx, ecx             ; проверяем деление на 0
    jz zero_div
    div ecx                   ; 34 / b
    movsx ebx, ax             ; сохраняем результат деления в ebx как знаковый (для последующей операции)

    movsx eax, word [usa]     ; загружаем a (как знаковое значение)
    sub ebx, eax              ; знаменатель = (34 / b) - a
    add ebx, 1                ; знаменатель = (34 / b) - a + 1

    ; Проверка и сохранение знаменателя
    mov [usDen], ebx          ; сохраняем знаменатель

    ; Выполнение деления: Числитель / Знаменатель
    mov eax, [usNum]          ; загружаем числитель
    cdq                       ; расширяем для знакового деления

    mov ecx, [usDen]          ; загружаем знаменатель
    test ecx, ecx             ; проверяем деление на 0
    jz zero_div
    idiv ecx                  ; выполняем знаковое деление: результат = числитель / знаменатель
    mov [usRes], eax          ; сохраняем результат

    ret
