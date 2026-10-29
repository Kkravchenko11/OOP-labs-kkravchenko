#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Header.h"
using namespace std;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Complex first;
    first.Init(5, 4);
    cout << "Перше число = ";
    first.Print();
    cout << endl;

    first.AddToParts(2, -10);
    cout << "Перше число після AddToParts(2, -10) = ";
    first.Print();
    cout << endl;

    Complex second(1.5, 3);
    Complex sum = first.Add(second);
    cout << "Сума першого і другого = ";
    sum.Print();
    cout << endl;

    Complex* array = nullptr;
    int count = 0;
    if (!ReadComplexArray("test.txt", array, count))
    {
        cout << "Не вдалося прочитати test.txt" << endl;
        return 1;
    }

    cout << endl << "Числа з файлу:" << endl;
    PrintArray(array, count);

    Complex total = SumArray(array, count);
    cout << "Сума всіх: ";
    total.Print();
    cout << endl;

    delete[] array;
    return 0;
}