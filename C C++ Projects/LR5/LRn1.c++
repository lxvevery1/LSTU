#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct CITIES 
    {
        string city;
        int year;
        int citizens;
    };
int main()
{
    setlocale(LC_ALL, "");
    int sumcitizens, maxcitizens; // ��������� ���-�� ������� � �������; ������������ ���-�� ������� � ������
    string mingorod, maxgorod, maxprirost; // ����� � ���������� ����������; ����� � ���������� ����������; ����� � ����� ������� ��������� ��������� �� ��������� ���

    int size, i;
    cout << "������� ���������� �������: ";
    cin >> size;
    CITIES *c = new CITIES[size];
    for (i = 0; i < size; i++)    
    {
        cout << "�����: "; cin >> c[i].city;
        cout << "���: "; cin >> c[i].year;
        cout << "������: "; cin >> c[i].citizens;
        sumcitizens += c[i].citizens; // ����� ���� �������
    }
    maxcitizens = c[0].citizens;
    maxgorod = c[0].city;
    for (i = 0; i < size; i++) //���� ������ ������ �������� ������+���������� ���������
    {
        if (c[i].citizens > maxcitizens)
        {
            maxcitizens = c[i].citizens;
            maxgorod = c[i].city;
        }
    }
    int mingorod1 = c[0].citizens;
    mingorod = c[0].city;
    for (i = 0; i < size; i++){
     //���� ������ ������ ���������� ������
        if (c[i].citizens < mingorod1){
        mingorod1 = c[i].citizens;
        mingorod = c[i].city;}
    }
    cout << "��������� ���-�� ������� � �������: " << sumcitizens << endl;
    cout << "������������ ���-�� ������� � ������: " << maxcitizens << endl;
    cout << "����� � ���������� ����������: " << maxgorod << endl;
    cout << "����� � ���������� ����������: " << mingorod << endl;
    cout << "����� � ����� ������� ��������� ��������� �� ��������� ���: " << maxprirost << endl; //��������� �������
    system("pause");
    return 0;
}