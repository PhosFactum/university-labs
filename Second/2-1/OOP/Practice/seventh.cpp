#include <iostream>
#include <string>

int main() {
    std::string str;       // Пустая строка
    size_t cap_old = str.capacity();  // Начальная ёмкость
    size_t cap_cur;
    int count = 0;         // Счётчик расширений

    // Цикл добавления символов в строку
    while (true) {
        // Добавляем символ в строку
        str.push_back('a');
        cap_cur = str.capacity();

        // Проверяем, изменилась ли ёмкость
        if (cap_cur != cap_old) {
            count++;
            cap_old = cap_cur; // Обновляем ёмкость
        }

        // Вывод информации
        std::cout << "Длина строки: " << str.size() 
                  << ", Текущая ёмкость: " << cap_cur 
                  << ", Количество расширений: " << count << std::endl;

        // Предложение пользователю продолжить или выйти
        char choice;
        std::cout << "Продолжить (y/n)? ";
        std::cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    // Вывод конечной длины строки
    std::cout << "Конечная длина строки: " << str.size() << std::endl;
    std::cout << "Общее количество расширений ёмкости: " << count << std::endl;

    return 0;
}

