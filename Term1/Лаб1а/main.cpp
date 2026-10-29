#include <iostream>
#include <windows.h>
#include "Header.h"
using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    Figure kr(10);
    Figure tr(10, 20);

    cout << "Площа круга: " << kr.area() << endl;
    cout << "Площа трикутника: " << tr.area() << endl;

    return 0;
}