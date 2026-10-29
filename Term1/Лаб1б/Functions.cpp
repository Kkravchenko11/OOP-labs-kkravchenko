#include <iostream>
#include "Header.h"
using namespace std;

void Complex::init(int x, int y)
{
    r = x;
    m = y;
}

void Complex::addInt(int x, int y)
{
    r += x;
    m += y;
}

Complex Complex::add(Complex c)
{
    Complex res;
    res.r = r + c.r;
    res.m = m + c.m;
    return res;
}

void Complex::print()
{
    if (m >= 0)
        cout << r << " + " << m << "i" << endl;
    else
        cout << r << " - " << -m << "i" << endl;
}