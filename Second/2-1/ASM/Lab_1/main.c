// main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// Глобальные переменные
extern int asm_sc(void);
extern int asm_ss(void);
extern int asm_uc(void);
extern int asm_us(void);

int8_t sca, scb, scd;
uint8_t uca, ucb, ucd;

int16_t ssa, ssb, ssd;
uint16_t usa, usb, usd;

int32_t scRes, scNum, scDen, ssRes, ssNum, ssDen;
int32_t ucRes, ucNum, ucDen, usRes, usNum, usDen;

// Функция для signed char
void process_sc() {
    int cNum, cDen, cRes;
    int temp_a, temp_b, temp_d;

    // Цикл для проверки правильного ввода значений sca, scb и scd
    do {
        printf("\nEnter 3 signed char a, b, d (-128 to 127, a, b = 0): ");
        if (scanf("%d %d %d", &temp_a, &temp_b, &temp_d) != 3) {
            printf("\nError: Invalid input. Please enter three valid numbers.\n\n");
            while (getchar() != '\n'); // Очищаем буфер
            continue; // Завершаем выполнение функции и возвращаемся в меню
        }

        // Проверка диапазонов для signed char
        if (temp_a < -128 || temp_a > 127 || temp_b < -128 || temp_b > 127 || temp_d < -128 || temp_d > 127) {
            printf("\nError: a, b, d out of range (-128 to 127). Try again.\n\n");
            continue; // Завершаем выполнение функции и возвращаемся в меню
        }

        // Присвоение значений после проверки диапазона
        sca = (int8_t)temp_a;
        scb = (int8_t)temp_b;
        scd = (int8_t)temp_d;

        // Проверка, что a и b не равны 0
        if (sca == 0 || scb == 0) {
            printf("\nError: a and b must not be 0. Try again.\n\n");
            continue; // Завершаем выполнение функции и возвращаемся в меню
        }
    } while (sca == 0 || scb == 0 || temp_a < -128 || temp_a > 127 || temp_b < -128 || temp_b > 127 || temp_d < -128 || temp_d > 127);

    // Вычисление результата на C
    cNum = (2 * scd - (96 / sca));
    cDen = ((34 / scb) - sca + 1);
    cRes = cNum / cDen;

    printf("\nC numerator: %d\nC denominator: %d\nC char signed result: %d\n", cNum, cDen, cRes);
    asm_sc();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ASM numerator: %d\nASM denominator: %d\nASM char signed result: %d\n", scNum, scDen, scRes);
}

// Функция для signed int
void process_ss() {
    int16_t cRes, cNum, cDen;
    int temp_a, temp_b, temp_d;

    // Цикл для проверки правильного ввода значений ssa, ssb и ssd
    do {
        printf("Enter 3 signed int a, b, d (-32768 to 32767, a, b = 0): ");
        if (scanf("%d %d %d", &temp_a, &temp_b, &temp_d) != 3) {
            printf("\nError: Invalid input. Please enter three valid numbers.\n\n");
            while (getchar() != '\n'); // Очищаем буфер
            continue;
        }

        // Проверка диапазонов для signed int
        if (temp_a < -32768 || temp_a > 32767 || temp_b < -32768 || temp_b > 32767 || temp_d < -32768 || temp_d > 32767) {
            printf("\nError: a, b, d out of range (-32768 to 32767). Try again.\n\n");
            continue;
        }

        // Присвоение значений после проверки диапазона
        ssa = (int16_t)temp_a;
        ssb = (int16_t)temp_b;
        ssd = (int16_t)temp_d;

        // Проверка, что a и b не равны 0
        if (ssa == 0 || ssb == 0) {
            printf("\nError: a and b must not be 0. Try again.\n\n");
        }
    } while (ssa == 0 || ssb == 0 || temp_a < -32768 || temp_a > 32767 || temp_b < -32768 || temp_b > 32767 || temp_d < -32768 || temp_d > 32767);

    // Вычисление результата на C
    cNum = (2 * ssd - (96 / ssa));
    cDen = ((34 / ssb) - ssa + 1);
    cRes = cNum / cDen;

    printf("\nC numerator: %d\nC denominator: %d\nC int signed result: %d\n", cNum, cDen, cRes);
    asm_ss();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ASM numerator: %d\nASM denominator: %d\nASM int signed result: %d\n", ssNum, ssDen, ssRes);
}

// Функция для unsigned char
void process_uc() {
    uint8_t cRes, cNum, cDen;
    int temp_a, temp_b, temp_d;

    // Цикл для проверки правильного ввода значений uca, ucb и ucd
    do {
        printf("Enter 3 unsigned char a, b, d (0 to 255, a, b = 0): ");
        if (scanf("%d %d %d", &temp_a, &temp_b, &temp_d) != 3) {
            printf("\nError: Invalid input. Please enter three valid numbers.\n\n");
            while (getchar() != '\n'); // Очищаем буфер
            continue;
        }

        // Проверка диапазонов для unsigned char
        if (temp_a < 0 || temp_a > 255 || temp_b < 0 || temp_b > 255 || temp_d < 0 || temp_d > 255) {
            printf("\nError: a, b, d out of range (0 to 255). Try again.\n\n");
            continue;
        }

        // Присвоение значений после проверки диапазона
        uca = (uint8_t)temp_a;
        ucb = (uint8_t)temp_b;
        ucd = (uint8_t)temp_d;

        // Проверка, что a и b не равны 0
        if (uca == 0 || ucb == 0) {
            printf("\nError: a and b must not be 0. Try again.\n\n");
        }
    } while (uca == 0 || ucb == 0 || temp_a < 0 || temp_a > 255 || temp_b < 0 || temp_b > 255 || temp_d < 0 || temp_d > 255);

    // Вычисление результата на C
    cNum = (2 * ucd - (96 / uca));
    cDen = ((34 / ucb) - uca + 1);
    cRes = cNum / cDen;

    printf("\nC numerator: %d\nC denominator: %d\nC char unsigned result: %d\n", cNum, cDen, cRes);
    asm_uc();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ASM numerator: %hhd\nASM denominator: %hhd\nASM char unsigned result: %hhd\n", ucNum, ucDen, ucRes);
}

// Функция для unsigned int
void process_us() {
    int32_t cRes, cNum, cDen;
    int temp_a, temp_b, temp_d;

    // Цикл для проверки правильного ввода значений usa, usb и usd
    do {
        printf("Enter 3 unsigned int a, b, d (0 to 65535, a, b = 0): ");
        if (scanf("%d %d %d", &temp_a, &temp_b, &temp_d) != 3) {
            printf("\nError: Invalid input. Please enter three valid numbers.\n\n");
            while (getchar() != '\n'); // Очищаем буфер
            continue;
        }

        // Проверка диапазонов для unsigned int
        if (temp_a < 0 || temp_a > 65535 || temp_b < 0 || temp_b > 65535 || temp_d < 0 || temp_d > 65535) {
            printf("\nError: a, b, d out of range (0 to 65535). Try again.\n\n");
            continue;
        }

        // Присвоение значений после проверки диапазона
        usa = (uint16_t)temp_a;
        usb = (uint16_t)temp_b;
        usd = (uint16_t)temp_d;

        // Проверка, что a и b не равны 0
        if (usa == 0 || usb == 0) {
            printf("\nError: a and b must not be 0. Try again.\n\n");
        }
    } while (usa == 0 || usb == 0 || temp_a < 0 || temp_a > 65535 || temp_b < 0 || temp_b > 65535 || temp_d < 0 || temp_d > 65535);
    // Вычисление результата на C
    cNum = (2 * usd - (96 / usa) );
    cDen = ( (34 / usb) - usa + 1);
    cRes = cNum / cDen;

    printf("\nC numerator: %d\nC denominator: %d\nC int unsigned result: %d\n", cNum, cDen, cRes);
    asm_us();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("ASM numerator: %d\nASM denominator: %hd\nASM int unsigned result: %d\n", usNum, usDen, usRes);
}


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


int main() {
    int choice = 0;

    printf("----- ASM EXPRESSION COUNTER -----");

    do {
        printf("\n\nSelect operation:\n");
        printf("1. Process signed char\n");
        printf("2. Process signed int\n");
        printf("3. Process unsigned char\n");
        printf("4. Process unsigned int\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nError: Invalid input. Please enter a valid number.");
            clear_input_buffer();  // Очищаем буфер ввода
            continue;  // Переходим к следующей итерации
        }

        // Проверка диапазона
        if (choice < 1 || choice > 5) {
            printf("\nError: Please select a number between 1 and 5.");
            clear_input_buffer();  // Очищаем буфер ввода, если число некорректное
            continue;  // Переходим к следующей итерации
        }

        switch (choice) {
            case 1:
                process_sc();
                break;
            case 2:
                process_ss();
                break;
            case 3:
                process_uc();
                break;
            case 4:
                process_us();
                break;
            case 5:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice, try again.");
        }
    } while (choice != 5);

    return 0;
}
