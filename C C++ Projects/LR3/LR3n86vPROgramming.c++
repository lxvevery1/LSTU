#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    int a;
    int b;

    cout << "������� �����: ";
    cin >> a;
    do
    {
        b = a % 10;
        a = a / 10;
    } 
    while (a>0);
cout << "������ ����� �����: " << b;
return 0;
}
