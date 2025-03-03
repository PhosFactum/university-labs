#include <iostream>

using namespace std;

class Integer {
public:
    Integer (int number) {
        value = number;
        cout << "Variable has been created!" << endl;
    }
    int getValue() {
        return value;
    }
    void setValue(int number) {
        value = number; 
    }
    void print(){
        cout << "Value: " << value << endl;
    }
private:
    int value;
};

int main() {
    Integer a {10};
    a.print();
    a.setValue(5);
    a.print();
    a.setValue(a.getValue() * 10);
    a.print();
}
