//43. ���� ��� �������������� �����. �������� � ������� �� �� ���, �������� ������� ��������������.
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<locale.h>
using namespace std;

int main(){
    float x, y, z;
    setlocale(LC_ALL, "");

    
    cout << "������� x: ";
    cin >>x;
    cout << "������� y: ";
    cin >>y;
    cout << "������� z: ";
    cin >>z;

    if (x>=0)
    cout << endl <<"x = " << x*x <<endl;
    if (y>=0)
    cout << endl <<"y = " << y*y <<endl;
    if (z>=0)
    cout << endl <<"z = " << z*z <<endl;
}
