#ifndef STATICARRAY_H
#define STATICARRAY_H

#include <iostream>
#include <stdexcept>

template <typename T, size_t N>
class StaticArray {
private:
    T data[N];  // Массив фиксированного размера

public:
    // Конструктор по умолчанию
    StaticArray() {
        for (size_t i = 0; i < N; i++) {
            data[i] = T();  // Инициализация значением по умолчанию
        }
    }

    // Доступ к элементу (оператор [])
    T& operator[](size_t index) {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Доступ к элементу (оператор [] для константного объекта)
    const T& operator[](size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Метод для получения размера массива
    size_t size() const {
        return N;
    }

    // Метод для вывода содержимого массива
    void display() const {
        for (size_t i = 0; i < N; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif // STATICARRAY_H

