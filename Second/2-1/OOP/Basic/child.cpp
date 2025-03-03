#include <iostream>

using namespace std;

class Children {
private:
    string name = "Max";
    string surname = "K";
    int age = 19;
public:
    Children() {  // Constructor (by default)
        cout << "This is a child!" << endl;
    }

    ~Children() {  // Destructor (freeing mem)
        cout << "Bye!" << endl;
    }

    void displayData() {
        cout << "Name: " << name << ", Surname: " << surname << ", Age: " << age << "." << endl;
    }
};

int main() {
    Children Max;
    Max.displayData();

    return 0;
}
