// main.cpp

#include "classes.h"
#include <iostream>

int main() {
    // Пример работы с классом COne
    std::cout << "=== Пример работы с COne ===\n";
    COne oneObj1(10, "Example1");
    oneObj1.print();
    COne oneObj2 = oneObj1;   // Проверка конструктора копирования
    oneObj2.print();

    // Пример работы с классом CTwo
    std::cout << "\n=== Пример работы с CTwo ===\n";
    CTwo twoObj1(3.14, &oneObj1);  // CTwo включает COne
    twoObj1.print();

    CTwo twoObj2 = twoObj1;  // Проверка конструктора копирования
    twoObj2.print();

    // Пример работы с классом CThree
    std::cout << "\n=== Пример работы с CThree ===\n";
    CThree threeObj1(2.71, &oneObj1, 42);
    threeObj1.print();
    std::cout << "Дополнительное поле threeObj1: " << threeObj1.getAdditionalField() << std::endl;

    // Пример работы с классом CFour
    std::cout << "\n=== Пример работы с CFour ===\n";
    CFour fourObj1(1.61, &oneObj1, 100, "ExtraData");
    fourObj1.print();
    std::cout << "Дополнительное поле fourObj1: " << fourObj1.getExtraField() << std::endl;

    // Демонстрация работы полиморфной функции printAll
    std::cout << "\n=== Пример работы printAll с полиморфизмом ===\n";
    CTwo* objects[] = { &twoObj1, &threeObj1, &fourObj1 };
    int n = sizeof(objects) / sizeof(objects[0]);
    printAll(objects, n);

    return 0;
}

