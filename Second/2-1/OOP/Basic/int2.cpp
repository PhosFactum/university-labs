#include <iostream>

using namespace std;

class Integer 
{
public:
    Integer(int number);   
    int getValue();
    void setValue(int number);
    void print();
private:
    int value;
};
Integer::Integer (int number) 
{
    value = number;
    cout << "Variable has been created!" << endl;
}
int Integer::getValue() { return value; }
void Integer::setValue(int number) { value = number; }
void Integer::print()
{ 
    cout << "Value: " << value << endl;
}

int main() {
    Integer a {10};
    a.print();
    a.setValue(5);
    a.print();
    a.setValue(a.getValue() * 10);
    a.print();
}
