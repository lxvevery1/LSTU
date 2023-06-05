#include<iostream>
#include<iomanip>
#include <vector>
 
using namespace std;
 
typedef vector< vector<int> > MatrixInt;
 
int main() {
    size_t rows = 5, cols = 5;       // ������������� ����������
    MatrixInt v(rows);
    for (auto &array : v)
        array.resize(cols);
 
    // ������������ ��������
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            v[i][j] = (i + 1) * 10 + (j + 1);
    }
 
    // ����� �������� �� �������
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            cout << setw(4) << v[i][j];
        cout << endl;
    }
}