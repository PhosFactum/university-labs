// classes.cpp

#include "classes.h"
#include <iostream>

// Реализация COne
COne::COne() : n(0), s("") { std::cout << "Конструктор COne по умолчанию\n"; }
COne::COne(int n_val, const std::string& s_val) : n(n_val), s(s_val) { std::cout << "Конструктор COne с параметрами\n"; }
COne::COne(const COne& other) : n(other.n), s(other.s) { std::cout << "Конструктор копирования COne\n"; }
COne::~COne() { std::cout << "Деструктор COne\n"; }
COne& COne::operator=(const COne& other) {
    if (this != &other) {
        n = other.n;
        s = other.s;
    }
    return *this;
}
void COne::print() const { std::cout << "COne: n = " << n << ", s = " << s << std::endl; }
std::string COne::toString() const { return "COne: n = " + std::to_string(n) + ", s = " + s; }  // Реализация toString


// Реализация CTwo
CTwo::CTwo() : d(0.0), p(nullptr) { std::cout << "Конструктор CTwo по умолчанию\n"; }
CTwo::CTwo(double d_val, COne* p_val) : d(d_val), p(p_val ? new COne(*p_val) : nullptr) { std::cout << "Конструктор CTwo с параметрами\n"; }
CTwo::CTwo(const CTwo& other) : d(other.d), p(other.p ? new COne(*other.p) : nullptr) { std::cout << "Конструктор копирования CTwo\n"; }
CTwo::~CTwo() { delete p; std::cout << "Деструктор CTwo\n"; }
CTwo& CTwo::operator=(const CTwo& other) {
    if (this != &other) {
        d = other.d;
        delete p;
        p = other.p ? new COne(*other.p) : nullptr;
    }
    return *this;
}
void CTwo::print() const {
    std::cout << "CTwo: d = " << d;
    if (p) { std::cout << ", p -> "; p->print(); }
    else { std::cout << ", p = nullptr\n"; }
}

// Реализация CThree
CThree::CThree() : CTwo(), additionalField(0) { std::cout << "Конструктор CThree по умолчанию\n"; }
CThree::CThree(double d_val, COne* p_val, int add_field) : CTwo(d_val, p_val), additionalField(add_field) { std::cout << "Конструктор CThree с параметрами\n"; }
CThree::CThree(const CThree& other) : CTwo(other), additionalField(other.additionalField) { std::cout << "Конструктор копирования CThree\n"; }
CThree::~CThree() { std::cout << "Деструктор CThree\n"; }
CThree& CThree::operator=(const CThree& other) {
    if (this != &other) {
        CTwo::operator=(other);
        additionalField = other.additionalField;
    }
    return *this;
}
void CThree::print() const {
    CTwo::print();
    std::cout << "CThree: additionalField = " << additionalField << std::endl;
}

// Реализация CFour
CFour::CFour() : CThree(), extraField("") { std::cout << "Конструктор CFour по умолчанию\n"; }
CFour::CFour(double d_val, COne* p_val, int add_field, const std::string& extra) : CThree(d_val, p_val, add_field), extraField(extra) { std::cout << "Конструктор CFour с параметрами\n"; }
CFour::CFour(const CFour& other) : CThree(other), extraField(other.extraField) { std::cout << "Конструктор копирования CFour\n"; }
CFour::~CFour() { std::cout << "Деструктор CFour\n"; }
CFour& CFour::operator=(const CFour& other) {
    if (this != &other) {
        CThree::operator=(other);
        extraField = other.extraField;
    }
    return *this;
}
void CFour::print() const {
    CThree::print();
    std::cout << "CFour: extraField = " << extraField << std::endl;
}

// Глобальная функция printAll
void printAll(CTwo* objects[], int n) {
    for (int i = 0; i < n; ++i) {
        objects[i]->print();
        std::cout << "--------" << std::endl;
    }
}

