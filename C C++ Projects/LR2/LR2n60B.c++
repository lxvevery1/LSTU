//60. ����� D � �������������� ����� ��������� (���. 1, ��3, �) � ����� u ������������ �� x � y ��������� ������� (������ (x, y) ? D ��������, ��� ����� � ������������ x, y ����������� D)

#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<locale.h>
#include<math.h>
using namespace std;

int main(){
    float u, x, y;
    setlocale(LC_ALL, "");

    cout << "������� x: ";
    cin >>x;
    cout << "������� y: ";
    cin >>y;

    if (((sqrt(x)+sqrt(y-1))<1) && (y<(1-sqrt(x))))
        std::cout << (u = x-y);
    else 
        std::cout << (u = x*y + 7);
    

     
return 0;
}