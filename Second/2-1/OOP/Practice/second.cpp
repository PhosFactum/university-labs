#include <iostream>
#include <string>
using std :: cout;
using std :: cin;
using std :: endl;
using std :: string;
int main()
{
string str("1234"); // Контролируемая операция – конструктор -
// преобразователь типа
cout << "str-> " << str << endl;
cout << "-----------------------------------------" << endl;
cout << "str.length() = " << str.length() << endl;
cout << "-----------------------------------------" << endl;
cout << "str.capacity() = " << str.capacity() << endl;
cout << "-----------------------------------------" << endl;
return 0;
}
