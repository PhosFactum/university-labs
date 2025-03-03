// main.c
// (b+a)/(a-1) , если a > b
// 23 , если a = b
// b*b/8 , если a < b

#include <stdio.h>
#include <string.h>
#include <limits.h>

int a_signed;                   // a - знаковое целое для signed
unsigned int a_unsigned;        // a - беззнаковое целое для unsigned
int b_signed;                   // b - знаковое целое для signed
unsigned int b_unsigned;        // b - беззнаковое целое для unsigned
long long X_signed;             // Результат для знаковых
unsigned long long X_unsigned;  // Результат для беззнаковых

// Прототипы функций ASM
void calculate_expression_signed();
void calculate_expression_unsigned();

void clear_input_buffer() {
    while (getchar() != '\n');  // Очищаем буфер ввода
}

void input_data_signed() {
    char input[100];
    long long temp_a, temp_b;

    printf("Введите значения для знаковых a и b (-2147483648 до 2147483647): ");
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Ошибка ввода! Попробуйте снова: ");
            continue;
        }
        
        if (sscanf(input, "%lld %lld", &temp_a, &temp_b) == 2) {
            if (temp_a < INT_MIN || temp_a > INT_MAX) {
                printf("Значение a выходит за диапазон int (-2147483648 до 2147483647). Попробуйте снова: ");
                continue;
            }
            if (temp_b < INT_MIN || temp_b > INT_MAX) {
                printf("Значение b выходит за диапазон int (-2147483648 до 2147483647). Попробуйте снова: ");
                continue;
            }
            if (temp_a == 1) {
                printf("Некорректный ввод! Значение a не должно быть равно 1. Попробуйте снова: ");
                continue;
            }
            a_signed = (int)temp_a;
            b_signed = (int)temp_b;
            break;
        } else {
            printf("Некорректный ввод! Введите два целых числа для a и b: ");
        }
    }
}

void input_data_unsigned() {
    char input[100];
    unsigned long long temp_a, temp_b;

    printf("Введите значения для беззнаковых a и b (0 до 4294967295): ");
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Ошибка ввода! Попробуйте снова: ");
            continue;
        }
        
        if (sscanf(input, "%llu %llu", &temp_a, &temp_b) == 2) {
            if (temp_a > UINT_MAX) {
                printf("Значение a выходит за диапазон unsigned int (0 до 4294967295). Попробуйте снова: ");
                continue;
            }
            if (temp_b > UINT_MAX) {
                printf("Значение b выходит за диапазон unsigned int (0 до 4294967295). Попробуйте снова: ");
                continue;
            }
            a_unsigned = (unsigned int)temp_a;
            b_unsigned = (unsigned int)temp_b;
            break;
        } else {
            printf("Некорректный ввод! Введите два числа для a и b: ");
        }
    }
}

void perform_signed_operation() {
    input_data_signed();
    calculate_expression_signed();
    printf("Результат X (signed): %lld\n", X_signed);
}

void perform_unsigned_operation() {
    input_data_unsigned();
    calculate_expression_unsigned();
    printf("Результат X (unsigned): %llu\n", X_unsigned);
}

int main() {
    int choice;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Выполнить операцию для знаковых значений\n");
        printf("2. Выполнить операцию для беззнаковых значений\n");
        printf("0. Выход\n");
        printf("Выберите опцию: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Некорректный ввод! Попробуйте снова.\n");
            clear_input_buffer();
            continue;
        }
        
        clear_input_buffer();

        if (choice == 1) {
            perform_signed_operation();
        } else if (choice == 2) {
            perform_unsigned_operation();
        } else if (choice == 0) {
            printf("Программа завершена.\n");
            break;
        } else {
            printf("Некорректный выбор! Попробуйте снова.\n");
        }
    }

    return 0;
}


