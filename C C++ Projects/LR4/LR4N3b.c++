#include <iostream>
using namespace std;

void sdvig(int* array, int sdvig, int n)
{
for (int i = sdvig; i < n-1; i++)
array[i] = array[i + 1];
}

int main()
{
    setlocale(LC_ALL, "");
    int n, delta = 0; //���������� ������� �� ���-�� ����������� �����
    cout << "������� ���������� ��������� �������: ";
    cin >> n;
    int* array;
    array = (int*)malloc(sizeof (int) * n); //������� ������
    if (!array) 
    return 1;
    cout << "������� ������: ";
    for (int i = 0; i < n; i++)
    cin >> array[i];

    for (int i = 0; i < n; i++) // ������ ��������� �������
    cout << array[i] << " ";
    cout << endl;

    for (int i = 0; i < n - delta - 1; i++) //����� ����������� �����
    for (int j = i+1; j < n - delta ; j++)
    {
        if (array[i] == array[j]) { sdvig(array, n, j); delta++; j--; } //���� ���� ����������� ����� - ��������
    }

    int* check = (int*)realloc(array, sizeof(int) * (n - delta)); //����������� ������ ������ delta
    if (check) array = check; 
    else return 1;

    for (int i = 0; i < n - delta; i++) // ����� �����
    cout << array[i] << " ";

    free(array); //������� ������
}