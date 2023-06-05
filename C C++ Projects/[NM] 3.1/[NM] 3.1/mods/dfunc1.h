// dfunc1.h  functions of one variable f(x)
// ����� � ����� http://prografix.narod.ru

class MathFunc1
{
public:
	//virtual double operator () (double) const = 0;
	virtual double operator () (double) = 0;
};

// ������ ������-�����������:
/*
class Polynom5 : public MathFunc1
{
public:
	double a, b, c, d, e;

	double operator () (double t) const
	{
		return e + t * (d + t * (c + t * (b + t * (a + t))));
	}
};

*/

//************************* 03.12.2005 **************************************//
// ����� ���� ������� �� �������� ���������
// �������� ������� � ax � bx ������ ����� ������ �����
// tol - �������� ��������, 
// res - ��������� ������ 
bool zeroin(double ax, double bx, MathFunc1 & func, double tol, double & res);

//************************* 26.04.2010 **************************************//
// ����� �������� ��� ��������� ������� �� �������� ���������, ���������� x, ��� ������� ����������� ��������� 
double fmin(double a, double b, MathFunc1 & func, double eps);
double fmax(double a, double b, MathFunc1 & func, double eps);

// ��������� �������������� ������� �������� � ��������� ���������� ����� �� ������ ����
double Simpson(double a, double b, MathFunc1 & f, double eps);
