//33. ��������� ������ � ����
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<locale.h>
//������ �33 �� ���������
int main()
{
//��������� ���������� - ����� �����
setlocale(LC_ALL, "");
int x, y;
//���������� ������� ��������
//�� ������ ��������� ����� ����� ������� ��������� �� "Lucida Console"
SetConsoleOutputCP(1251); //�� �����
SetConsoleCP(1251); //�� ���� - � ���� ��������� �� �����������
//����������� �������� ���������� � ����������
printf("������� �������� x ");
scanf("%d", &x);
printf("������� �������� y ");
scanf("%d", &y);
printf("������� �)\n");
if(x>y)
printf("max=x=%d\n",x);
else
printf("max=y=%d\n",y);
printf("������� �)\n");
if(x<y) {
printf("min=x=%d\n",x);
}
else {
printf("min=y=%d\n",y);
}
printf("������� �)\n");
if(x<y)
{
printf("min=x=%d\n",x);
printf("max=y=%d\n",y);
}
else
{
printf("min=y=%d\n",y);
printf("max=x=%d\n",x);
}
getch();
return 0;
}
