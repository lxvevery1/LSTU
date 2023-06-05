#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;
unsigned integer(istream& inp, const char* msg) {
cout << msg;
unsigned value;
inp >> value;
inp.ignore(inp.rdbuf()->in_avail());
return value;
}
struct Home {
unsigned number;
unsigned level;
char name[0x30];
Home() : number(0), level(0) {
memset(name, 0, sizeof(name));
}
friend istream& operator>>(istream& inp, Home& h) {
cout << "�������� �����: ";
inp.getline(h.name, size(h.name));
h.number = integer(inp, "����� ����: ");
h.level = integer(inp, "���������� ������: ");
return inp;
}
friend ostream& operator<<(ostream& out, const Home& h) {
return out << "����� " << h.name << ", ��� " << h.number << ", ������: " << h.level;
}
} ;
void show(const char* title, Home* box, const size_t n) {
cout << '\t' << title << '\n';
for (auto i = 0U; i < n; ++i) cout << box[i] << '\n';
puts("");
}
int main() {
system("chcp 1251 > nul");
Home box[5];
for (auto& x : box) cin >> x;
box[size(box) - 1].level = 12;
show("����� ��������� ��������� � ��������� ������:", box, size(box));
cout << "����� " << box[1].name << "\n\n";
auto count = 0U;
auto num = integer(cin, "������� ����� ����: ");
for (const auto& x : box) {
if (x.number == num) {
cout << x << '\n';
++count;
break;
}
}
cout << "�����: ������� " << count << " ����������\n";
size_t i, j;
do {
i = integer(cin, "������� ������ ������: ");
} while (!i || i >= size(box));
do {
j = integer(cin, "������� ������ ������: ");
} while (!j || j >= size(box) || j == i);
swap(box[i], box[j]);
show("����� ������: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return string(a.name) > string(b.name);
} );
show("����� ���������� �� ��������: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return a.number > b.number;
} );
show("����� ���������� �� ������ ����: ", box, size(box));
sort(begin(box), end(box), [](const Home& a, const Home& b) {
return a.level > b.level;
} );
show("����� ���������� �� ���������: ", box, size(box));
do {
i = integer(cin, "������� ������: ");
} while (!i || i >= size(box));
cout << box[i] << '\n';
do {
i = integer(cin, "������� ������ ������ ���������: ");
} while (!i || i >= size(box));
do {
j = integer(cin, "������� ������ ������ ���������: ");
} while (!j || j >= size(box) || j == i);
for (auto f = i; f <= j; ++f) cout << box[f] << '\n';
system("pause > nul");
}