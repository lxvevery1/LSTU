//47. ���� �������������� ������������� ����� x, y, z. 
//a)�������� ���������� �� ����������� � ������� ������ x, y, z.
//b)���� ����������� ����������, �� �������� - �������� �� �� �������������.
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

    if (x+y>z || x+z>y || y+z>x)
        std::cout << "a) ����������� ����������.\n";
    else
        std::cout << "a) ����������� �� ���������.\n";
    // ���� ������� ����� ������� ������� ������������ ������ ����� ��������� ���� ������ ��� ������, �� ���� ����������� �������� �������������. 
    if (x*x+y*y<z*z || x*x+z*z<y*y || y*y+z*z<x*x)
        std::cout << "�) ����������� �������������.\n";

}
