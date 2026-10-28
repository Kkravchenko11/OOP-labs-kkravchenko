#include <iostream>
#include <windows.h>
using namespace std;

class Figure
{
private:
    double a;
    double b;
public:
    Figure(double x, double y = 0)
    {
        a = x;
        b = y;
    }

    double area()
    {
        if (b == 0)
            return 3.14159265 * a * a;
        return 0.5 * a * b;
    }
};

int main()
{
    SetConsoleOutputCP(65001);
    Figure kr(10);
    Figure tr(10, 20);

    cout << "Площа круга: " << kr.area() << endl;
    cout << "Площа трикутника: " << tr.area() << endl;

    return 0;
}