#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    double a, x = 1.0, n = 1.0;

    do
    {
        cout << "������� ����� a>1 a = ";
        cin >> a;
    } while (a<=1.0);

    do
    {
        n = n + 1;
        x = x+1/n;
    } while (x<=a);
    cout << "x(�����) = " << x << "\nn(����� �����) = " << n;
    return 0;
}
