//42. ���� �������������� ����� x, y(x!=y). ������� �� ���� ���� ����� ����� �������� �� ����������, � ������� - �� ��������� �������������.
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<windows.h>
#include<locale.h>
using namespace std;

int main(){
    float x, y;
    setlocale(LC_ALL, "");

    cout << "������� x: ";
    cin >>x;
    cout << "������� y: ";
    cin >>y;
 
    if (x>y) 
    cout <<endl <<"x = " << 2*(x*y) <<endl <<"y = " << (x+y)/2 << endl;
    else if (x<y)
    cout <<endl <<"x = " << (x+y)/2 <<endl <<"y = " << 2*(x+y) << endl;
    else if (x=y)
    cout << "���������� �� ������ ���� �����!";
    
    
    
    return 0;
}