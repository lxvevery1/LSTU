#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    setlocale (LC_ALL, "");
    unsigned i, G, N;
    while (true)
    {
        cout << "������� ��������� ��� G: ";
        cin >> G;
        cout << "������� ���������� ��� N: ";
        cin >> N;
        float delta, s, *osadki = new float [N];
        cout << "������� ������ ������������� ��������� �������: ";
        s = 0.0;
        for (i = 0; i < N; i++)        
    {
        cin >> osadki[i];
        s += osadki[i]; 
    }
        s /= N;
        cout << "������� ���������� �������: " << s << endl;
        for (i = 0; i < N; i++)
    {
        delta = osadki[i] - s;
        if (delta > 0)
        {
            cout << G + i << fixed << setprecision(3) << " > " << osadki[i] << " > "
            << fixed << setprecision(3) << "+"
            << delta << " > " << 100 * delta / s << " %" << endl;
        }
        else
        {
            cout << G + i << fixed << setprecision(3) << " > " << osadki[i] << " > "
            << fixed << setprecision(3)
            << delta << " > " << 100 * delta / s << " %" << endl;
        }
    }
    system("pause");
    return 0;
    }
}