// classes.h

#ifndef CLASSES_H
#define CLASSES_H

#include <string>

// Класс COne
class COne {
private:
    int n;
    std::string s;

public:
    COne();
    COne(int n_val, const std::string& s_val);
    COne(const COne& other);
    ~COne();

    COne& operator=(const COne& other);
    void print() const;
    std::string toString() const;  // Добавлен метод toString

    int getN() const { return n; }
    std::string getS() const { return s; }
};

// Класс CTwo
class CTwo {
protected:
    double d;
    COne* p;

public:
    CTwo();
    CTwo(double d_val, COne* p_val);
    CTwo(const CTwo& other);
    virtual ~CTwo();

    CTwo& operator=(const CTwo& other);
    virtual void print() const;

    double getD() const { return d; }  // Геттер для d
    COne* getP() const { return p; }   // Геттер для p
};

// Класс CThree, наследуемый от CTwo
class CThree : public CTwo {
private:
    int additionalField;

public:
    CThree();
    CThree(double d_val, COne* p_val, int add_field);
    CThree(const CThree& other);
    ~CThree();

    CThree& operator=(const CThree& other);
    void print() const override;

    int getAdditionalField() const { return additionalField; }  // Геттер для additionalField
};

// Класс CFour, наследуемый от CThree
class CFour : public CThree {
private:
    std::string extraField;

public:
    CFour();
    CFour(double d_val, COne* p_val, int add_field, const std::string& extra);
    CFour(const CFour& other);
    ~CFour();

    CFour& operator=(const CFour& other);
    void print() const override;

    std::string getExtraField() const { return extraField; }  // Геттер для extraField
};

// Глобальная функция для вывода всех объектов
void printAll(CTwo* objects[], int n);

#endif // CLASSES_H

