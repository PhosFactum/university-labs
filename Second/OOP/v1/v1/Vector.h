#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

using namespace std;

template <class T>
class Vector {
private:

    // Текущий размер массива
    int currentSize_ = 0;
    // Резервируемый размер массива (maximumSize_ >= currentSize_)
    int maximumSize_ = 10;
    // Указатель на массив из maximumSize_ элементов
    T *valuesList_ = nullptr;

protected:

    // Стандартное количество резервируемых элементов в массиве
    int standartMaximumSize = 10;

public:

    // Конструктор
    explicit Vector(int selectedSize = 0) {
        this->currentSize_ = selectedSize;
        if (selectedSize >= maximumSize_) {
            maximumSize_ = selectedSize * 2;
        }
        valuesList_ = new T[maximumSize_] {};
    }

    // Конструктор копирования
    Vector(const Vector &selectedVector) : Vector(selectedVector.currentSize_) {
        currentSize_ = selectedVector.currentSize_;
        std::copy(selectedVector.valuesList_, selectedVector.valuesList_ + currentSize_, valuesList_);
    }

    // Оператор копирования
    Vector &operator=(const Vector &selectedVector){
        Vector temp(selectedVector);
        swap(*this, temp);
        return *this;
    }

    // Конструктор перемещения
    Vector(Vector &&selectedVector) noexcept {
        this->currentSize_ = selectedVector.currentSize_;
        this->maximumSize_ = selectedVector.maximumSize_;
        this->valuesList_ = selectedVector.valuesList_;
        this->standartMaximumSize = selectedVector.standartMaximumSize;
        selectedVector.currentSize_ = 0;
        selectedVector.maximumSize_ = 0;
        selectedVector.valuesList_ = nullptr;
    }

    // Оператор перемещения
    Vector &operator=(Vector &&selectedVector) noexcept {
        if (this != &selectedVector) {
            swap(*this, selectedVector);
            delete[] selectedVector.valuesList_;
            selectedVector.valuesList_ = nullptr;
            selectedVector.currentSize_ = 0;
            selectedVector.maximumSize_ = 0;
        }
        return *this;
    }

    // Деструктор
    virtual ~Vector() {
        delete[] this->valuesList_;
    }

    // Оператор получения элемента по индексу I
    T &operator[](int index) {
        return this->valuesList_[index];
    }

    // [static] Получение размера массива
    static int size(const Vector &selectedVector) {
        return selectedVector.currentSize_;
    }

    // Добавление countAddedElements элементов из массива selectedVector в конец
    void add(const Vector &selectedVector, const int &countAddedElements) {
        int lastIndex = min(Vector::size(selectedVector), countAddedElements);
        for (int i = 0; i < lastIndex; ++i) {
            push_back(selectedVector.valuesList_[i]);
        }
    }

    // Вставка элемента value в позицию index
    void insert(const T &value, const int &index) noexcept(false) {
        if (index == 0) {
            push_front(value);
            return;
        } else if (index == this->currentSize_) {
            push_back(value);
            return;
        } else if (index > 0 && index < this->currentSize_) {
            push_back(value);
            T currentElement = valuesList_[index];
            T previousElement;
            for (int i = index; i < this->currentSize_; ++i) {
                previousElement = this->valuesList_[i];
                this->valuesList_[i] = currentElement;
                currentElement = previousElement;
            }
            this->valuesList_[index] = value;
            return;
        }
        throw out_of_range("Vector. Method insert. Out of range");
    }

    // Добавление элемента value в конец
    void push_back(const T &value) {
        if (this->currentSize_ < this->maximumSize_) {
            this->valuesList_[this->currentSize_] = value;
            ++this->currentSize_;
            return;
        }
        T *lastValuesList = this->valuesList_;
        this->valuesList_ = new T[this->maximumSize_ * 2] {};
        copy(lastValuesList, lastValuesList + this->currentSize_, this->valuesList_);
        delete[] lastValuesList;
        this->maximumSize_ *= 2;
    }

    // Добавление элемента value в начало
    void push_front(const T &value) {
        push_back(value);
        T t = this->valuesList_[0];
        T p;
        for (int i = 1; i < this->currentSize_; ++i) {
            p = this->valuesList_[i];
            this->valuesList_[i] = t;
            t = p;
        }
        this->valuesList_[0] = value;
    }

    // Очистка массива
    void clear() {
        delete[] this->valuesList_;
        this->valuesList_ = new T[this->standartMaximumSize] {};
        this->currentSize_ = 0;
        this->maximumSize_ = standartMaximumSize;
    }

    // Получение размера массива
    int size()  const noexcept { return this->currentSize_; }

    // Пустой ли массив
    bool empty() const noexcept { return this->currentSize_ == 0; }

    // Удаление элемента с индексом index
    T erase(int index) noexcept(false) {
        if (this->currentSize_ > 0 && index < this->currentSize_) {
            T deletedElement = this->valuesList_[index];
            copy(this->valuesList_ + index + 1, this->valuesList_ + this->currentSize_, this->valuesList_ + index);
            --this->currentSize_;
            return deletedElement;
        }
        throw out_of_range("Vector. Method erase. Out of range");
    }

    // Удаление первого (нулевого) элемента
    T pop_front() {
        return erase(0);
    }

    // Удаление последнего элемента
    T pop_back() {
        T deletedElement = T();
        if (this->currentSize_ > 0) {
            deletedElement = this->valuesList_[this->currentSize_ - 1];
            --this->currentSize_;
        }
        return deletedElement;
    }

    // Оператор приведения к типу bool
    explicit operator bool() {
        return this->currentSize_ != 0;
    }

    friend void swap(Vector &firstVector, Vector &secondVector) noexcept {
        swap(firstVector.standartMaximumSize, secondVector.standartMaximumSize);
        swap(firstVector.valuesList_, secondVector.valuesList_);
        swap(firstVector.maximumSize_, secondVector.maximumSize_);
        swap(firstVector.currentSize_, secondVector.currentSize_);
    }

    // Класс итератора по элементам
    class iterator {
    public:
        T *i;
        typedef random_access_iterator_tag  iterator_category;
        typedef ptrdiff_t  difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;

        inline iterator() : i(0) {}
        inline explicit iterator(T *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline T &operator*() const { return *i; }
        inline T *operator->() const { return i; }
        inline T &operator[](int j) const { return i[j]; }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline const iterator operator++(int) { T *n = i; ++i; return iterator(n); }
        inline iterator &operator--() { i--; return *this; }
        inline const iterator operator--(int) { T *n = i; i--; return iterator(n); }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return int(i - j.i); }
    };

    inline typename Vector<T>::iterator begin() { return iterator(&valuesList_[0]); }
    inline typename Vector<T>::iterator end() { return iterator(&valuesList_[currentSize_]); }

};

#endif // VECTOR_H
