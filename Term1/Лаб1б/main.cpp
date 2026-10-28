#include <iostream>
#include <windows.h>
using namespace std;

class Complex
{
private:
    int r;
    int m;
public:
    void init(int x, int y)
    {
        r = x;
        m = y;
    }

    void addInt(int x, int y)
    {
        r += x;
        m += y;
    }

    Complex add(Complex c)
    {
        Complex res;
        res.r = r + c.r;
        res.m = m + c.m;
        return res;
    }

    void print()
    {
        if (m >= 0)
            cout << r << " + " << m << "i" << endl;
        else
            cout << r << " - " << -m << "i" << endl;
    }
};

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