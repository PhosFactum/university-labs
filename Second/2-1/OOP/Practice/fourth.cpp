#include <iostream>
#include <string>
using std :: cout;
using std :: cin;
using std :: endl;
using std :: string;
int main()
{
string str1("1234567890");
cout << "str1-> " << str1 << endl;
cout << "-----------------------------------------" << endl;
cout << "str1.length() = " << str1.length() << endl;
cout << "-----------------------------------------" << endl;
cout << "str1.capacity() = " << str1.capacity() << endl;
cout << "-----------------------------------------" << endl;
string str2;
str2 = str1;
// Контролируемая операция – оператор присваивания
cout << "str2-> " << str2 << endl;
cout << "-----------------------------------------" << endl;
cout << "str2.length() = " << str2.length() << endl;
cout << "-----------------------------------------" << endl;
cout << "str2.capacity() = " << str2.capacity() << endl;
cout << "-----------------------------------------" << endl;
return 0;
}
