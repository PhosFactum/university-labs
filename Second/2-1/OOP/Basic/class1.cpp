#include <iostream>

class Person {
    
public:
    Person(std::string name, unsigned age) : name{name}, age{age} { }

    void print()
    {
        std::cout << "Name: " << name << "\tAge: " << age << std::endl;
    }

private:
    std::string name;
    unsigned age;

};

int main()
{
    Person bob("Bob", 22);
    bob.print();

    return 0;
}
