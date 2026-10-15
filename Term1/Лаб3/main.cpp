#include <iostream>
#include <windows.h>
#include "header.h"
using namespace std;

int main() {
	SetConsoleOutputCP(65001);

    B1 b1(1);
    B2 b2(2);
    B3 b3(3);
    D1 d1(11, 12, 13, 14);
    D3 d3(31, 32);
    D2 d2(21, 22, 23, 24, 25, 26);
    D4 d4(41, 42, 43, 44, 45, 46, 47);

    cout << "=== Виведення через operator<< ===" << endl;
    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << d1 << endl;
    cout << d3 << endl;
    cout << d2 << endl;
    cout << d4 << endl;

    cout << "\n=== Виклик show() ===" << endl;
    d4.show();
    cout << endl;

    cout << "\n=== Віртуальні функції через B2* ===" << endl;
    B2* p2[] = { &b2, &d1, &d2 };
    for (B2* p : p2) {
        p->show();
        cout << endl;
    }

    cout << "\n=== Віртуальні функції через B3* ===" << endl;
    B3* p3[] = { &b3, &d3 };
    for (B3* p : p3) {
        p->show();
        cout << endl;
    }

    cout << "\n=== Віртуальні функції через D1* ===" << endl;
    D1* pd1 = &d2;
    pd1->show();
    cout << endl;

    return 0;
}