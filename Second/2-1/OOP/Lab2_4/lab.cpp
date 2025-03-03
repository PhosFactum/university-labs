#include <iostream>
#include <string>
#include <cstring>

// Класс COne
class COne {
private:
    int n;
    std::string s;

public:
    COne() : n(0), s("") {
        std::cout << "Конструктор COne по умолчанию\n";
    }

    COne(int n_val, const std::string& s_val) : n(n_val), s(s_val) {
        std::cout << "Конструктор COne с параметрами\n";
    }

    COne(const COne& other) : n(other.n), s(other.s) {
        std::cout << "Конструктор копирования COne\n";
    }

    ~COne() {
        std::cout << "Деструктор COne\n";
    }

    COne& operator=(const COne& other) {
        if (this != &other) {
            n = other.n;
            s = other.s;
        }
        return *this;
    }

    void print() const {
        std::cout << "COne: n = " << n << ", s = " << s << std::endl;
    }
};

// Класс CTwo, включающий COne
class CTwo {
protected:
    double d;
    COne* p;

public:
    CTwo() : d(0.0), p(nullptr) {
        std::cout << "Конструктор CTwo по умолчанию\n";
    }

    CTwo(double d_val, COne* p_val) : d(d_val) {
        p = p_val ? new COne(*p_val) : nullptr;
        std::cout << "Конструктор CTwo с параметрами\n";
    }

    CTwo(const CTwo& other) : d(other.d) {
        p = other.p ? new COne(*other.p) : nullptr;
        std::cout << "Конструктор копирования CTwo\n";
    }

    virtual ~CTwo() {
        delete p;
        std::cout << "Деструктор CTwo\n";
    }

    CTwo& operator=(const CTwo& other) {
        if (this != &other) {
            d = other.d;
            delete p;
            p = other.p ? new COne(*other.p) : nullptr;
        }
        return *this;
    }

    virtual void print() const {
        std::cout << "CTwo: d = " << d;
        if (p) {
            std::cout << ", p -> ";
            p->print();
        } else {
            std::cout << ", p = nullptr" << std::endl;
        }
    }
};

// Класс CThree, наследуемый от CTwo
class CThree : public CTwo {
private:
    int additionalField;

public:
    CThree() : CTwo(), additionalField(0) {
        std::cout << "Конструктор CThree по умолчанию\n";
    }

    CThree(double d_val, COne* p_val, int add_field) : CTwo(d_val, p_val), additionalField(add_field) {
        std::cout << "Конструктор CThree с параметрами\n";
    }

    CThree(const CThree& other) : CTwo(other), additionalField(other.additionalField) {
        std::cout << "Конструктор копирования CThree\n";
    }

    ~CThree() {
        std::cout << "Деструктор CThree\n";
    }

    CThree& operator=(const CThree& other) {
        if (this != &other) {
            CTwo::operator=(other);
            additionalField = other.additionalField;
        }
        return *this;
    }

    void print() const override {
        CTwo::print();
        std::cout << "CThree: additionalField = " << additionalField << std::endl;
    }
};

// Класс CFour, наследуемый от CThree
class CFour : public CThree {
private:
    std::string extraField;

public:
    CFour() : CThree(), extraField("") {
        std::cout << "Конструктор CFour по умолчанию\n";
    }

    CFour(double d_val, COne* p_val, int add_field, const std::string& extra) 
        : CThree(d_val, p_val, add_field), extraField(extra) {
        std::cout << "Конструктор CFour с параметрами\n";
    }

    CFour(const CFour& other) : CThree(other), extraField(other.extraField) {
        std::cout << "Конструктор копирования CFour\n";
    }

    ~CFour() {
        std::cout << "Деструктор CFour\n";
    }

    CFour& operator=(const CFour& other) {
        if (this != &other) {
            CThree::operator=(other);
            extraField = other.extraField;
        }
        return *this;
    }

    void print() const override {
        CThree::print();
        std::cout << "CFour: extraField = " << extraField << std::endl;
    }
};

// Глобальная функция для вывода всех объектов в массиве
void printAll(CTwo* objects[], int n) {
    for (int i = 0; i < n; ++i) {
        objects[i]->print();
        std::cout << "--------" << std::endl;
    }
}

// Главная функция
int main() {
    COne oneObj(42, "Test String");
    CTwo twoObj(3.14, &oneObj);
    CThree threeObj(2.71, &oneObj, 42);
    CFour fourObj(1.61, &oneObj, 42, "Extra Data");

    CTwo* objects[] = {&twoObj, &threeObj, &fourObj};
    int n = sizeof(objects) / sizeof(objects[0]);

    printAll(objects, n);

    return 0;
}

