#include <iostream>
#include <windows.h>
#include "Header.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(65001);

    Complex a, b, c;

    a.init(5, 4);
    b.init(2, 3);

    cout << "Перше число: ";
    a.print();

    cout << "Друге число: ";
    b.print();

    a.addInt(1, 2);
    cout << "Після додавання цілих чисел: ";
    a.print();

    c = a.add(b);
    cout << "Сума: ";
    c.print();

    return 0;
}