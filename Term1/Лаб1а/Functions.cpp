#include "Header.h"

Figure::Figure(double x, double y)
{
    a = x;
    b = y;
}

double Figure::area()
{
    if (b == 0)
        return 3.14159265 * a * a;
    return 0.5 * a * b;
}