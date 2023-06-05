//100514 poly.h Polynons
//
#ifdef POLY
#error Secondary include
#endif
#define POLY

class polynom : public MathFunc1 {
private:
	int size;		// ������ �������
	int deg;		// �������, <=size-1. !������� �������� ���������� ����� -1!
	int rRoots;		// ���������� �������������� ������
	int cRoots;		// ���������� ��� ����������-����������� ������
					// deg = rRoots + 2*cRoots
	double *a;		// ������������
	double *roots;	// ����� ***


public:
	polynom();	// ������� ���������
	polynom(int size_);	// ������� ���������
	polynom(double a0, double a1);	// a0 + a1*x
	polynom(double a0, double a1, double a2); // a0 + a1*x + a2*x^2
	polynom(double a0, double a1, double a2, double a3); // a0 + a1*x + a2*x^2 + a3*x^3
	polynom(double a0, double a1, double a2, double a3, double a4); // a0 + a1*x + a2*x^2 + a3*x^3 + a4*x^4
	~polynom();
	void clear();					// �������� ������������
	void set(int k, double v);		// a[k] = v
	void setSize(int k);			// ���������� ������ >=k
	void calcDegree();				// ����� �������

	int Deg() { return deg; }		// �������
	double A(int i);				// ����������� ��� x^i
	int rRt() { return rRoots; }	// ���������� ��������� �������������� ������
	int cRt() { return cRoots; }	// ���������� ��������� ��� ����������-����������� ������
	double v(double x);	// �������� � �����
	double operator () (double t);
	double dv(double x);// �������� ����������� � �����
	double ddv(double x);// �������� 2-� ����������� � �����
	
	// ���������� ���������� ������
	int solveR();	// ����� �������������� ����� (������ ��� ������� 1,2,3,4)
					// ����� ����� � roots, ���������� ���������� ������
	double rRoot(int i);	// i-� �������������� ������
	double pRoot(int i);	// �������������� ����� i-�� ������������� �����
	double qRoot(int i);	// ������ ����� i-�� ������������� �����
private:
	void memRoots();	// �������� ������ ��� ������

	// f(x) mod (x^4+a*x3+b*x^2+c*x+d) = p3*x^3 + p2*x^2 + p1*x + p0
	void   mod4(double A, double b, double c, double d, double &p3, double &p2, double &p1, double &p0);
public:
	void add( polynom &b, double k);			// this += k*b
	void add( polynom &a, double ka, polynom &b, double kb);// this = ka*a + kb*b
	void Binom( double a0, double a1, int d);	// this = (a0 + x*a1)^d
	void Diff ( polynom &b);					// this = Diff(b);
	void mul(polynom &b, polynom &c);			// this = b*c
											//
	double RBorder();							// ������� ������� ������
	double NewtonStep( double x);				// return x-f(x)/f'(x)
	void   HichkokStep( double &a, double &b);	// one step of Hichkok method
	// ��� ��������:
	// ��������� ������

};



