#include "Rational.h"
#include "StaticArray.h"
#include <iostream>

int main() {
    try {
        // Создаём массив рациональных чисел
        StaticArray<Rational<int>, 5> array;

        // Заполняем массив
        for (size_t i = 0; i < array.size(); i++) {
            array[i] = Rational<int>(i + 1, i + 2);  // Пример: 1/2, 2/3, 3/4, ...
        }

        // Выводим содержимое массива
        std::cout << "Array contents:" << std::endl;
        for (size_t i = 0; i < array.size(); i++) {
            array[i].display();
        }

        // Пробуем обратиться к недопустимому индексу (генерация исключения)
        std::cout << "Accessing out-of-bounds index..." << std::endl;
        array[10].display();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

