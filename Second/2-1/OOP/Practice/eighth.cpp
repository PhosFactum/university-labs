#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string str;       // Пустая строка
    size_t cap_old = str.capacity();  // Начальная ёмкость
    size_t cap_cur;
    std::vector<size_t> expansions;  // Массив для хранения моментов расширения

    // Цикл добавления символов в строку
    for (int i = 0; i < 1000; ++i) {  // Увеличиваем длину строки до 1000 символов
        str.push_back('a');  // Добавляем символ в конец строки
        cap_cur = str.capacity();  // Текущая ёмкость строки

        // Проверяем, произошло ли расширение ёмкости
        if (cap_old != cap_cur) {
            // Расширение имело место
            expansions.push_back(cap_cur);  // Сохраняем новое значение ёмкости
            cap_old = cap_cur;  // Обновляем старое значение ёмкости
        }
    }

    // Вывод всех моментов расширения ёмкости
    std::cout << "Моменты расширения ёмкости строки: " << std::endl;
    for (size_t cap : expansions) {
        std::cout << cap << std::endl;
    }

    return 0;
}

