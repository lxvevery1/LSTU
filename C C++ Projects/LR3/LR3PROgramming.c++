/*N8:  1.	���������� ������� X ������������� �������, ����������� �������������� ������������������. ���������� ��������� � ������� (N) � ��� ������������������ (S) ������. ��������� ������� ������ ������������.
  2.	������ �������� ������� F(X) ��� ���������� ������� X � ����� �������� ������� ������������. ��� ������ �������� ������� ����������� � ���������������� �������.
  3.	������ ��������� ������� Y �� ������� Yi=G(Xi) � ����� �� ������������ � ���� */

#include <iostream>
#include <math.h>
using namespace std;


int main()
{
    setlocale(LC_ALL, "");

    double S = 5.5;
    int N = 13;
    double a1;
    

    cout << "������� ��������� �������: \na1 = "; cin >> a1;

    double*X = new double[N];                                   //������
    cout << "3.Yi = G(X): ";
    for (int i = 0; i < N; i++)
    {
       X[i]=a1+i*S;
        {
        if (X[i] < 15.0) 
        {
            cout.precision(4);
            cout << "\ny1 " << 13 * X[i] * X[i];
        }
        else if (X[i] > 70.0)
        {
            cout.precision(4); 
            cout << "\ny3 " << sqrt(X[i] - 1.0);
        }
        else if (X[i] >= 15 && X[i] <= 70)
        { 
            cout.precision(2); 
            cout << "\ny2 " << (6 - X[i]) / (X[i] * X[i] + 5.0);
        }
        }
    }
    

double Summa = 0;                                                //����� ���� ��. �������
    for (int i = 0; i < N; i++)
    {
    Summa = Summa + X[i];
    }
    cout << "\n2.�����: F(X) = " << scientific << Summa << "\n";
return 0;
}