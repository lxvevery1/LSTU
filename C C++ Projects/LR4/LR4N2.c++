#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    setlocale (LC_ALL, "");
    int N;
    while(true)
    {
        cout << "������� ���������� ����� N: ";
        cin >> N;

        auto a = new double [N]; //"������" ������
        auto b = new double [N]; //"����������" ������

        cout << "������� ����� a1, ... , aN: ";

        for(auto i = 0; i < N; ++i)   //���� ����� �������
        cin >> a[i];

        for(auto i = 1; i < N-1; i++)   //���� �������� �������            
        b[i] = (a[i-1] + a[i] + a[i+1])/3;

        b[0] = a[0];                  //���������� ������ ������� �������

        b[N-1] = a[N-1];              //���������� ��������� ������� �������

        for(auto i = 0; i < N; ++i)   //���� ������ �������
        cout << b[i] << endl;

        system("pause");
        return 0;
    }
}