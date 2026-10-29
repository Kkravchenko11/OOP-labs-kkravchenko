#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Header.h"
using namespace std;

Complex::Complex() : real_(0), imag_(0)
{
}

Complex::Complex(double real, double imag) : real_(real), imag_(imag)
{
}

void Complex::Init(double real, double imag)
{
    real_ = real;
    imag_ = imag;
}

void Complex::AddToParts(int addReal, int addImag)
{
    real_ += addReal;
    imag_ += addImag;
}

Complex Complex::Add(const Complex& other) const
{
    return Complex(real_ + other.real_, imag_ + other.imag_);
}

void Complex::Print() const
{
    if (imag_ < 0)
        cout << real_ << " - " << -imag_ << "i";
    else
        cout << real_ << " + " << imag_ << "i";
}

void Complex::Read(istream& in)
{
    in >> real_ >> imag_;
}

double Complex::GetReal() const
{
    return real_;
}

double Complex::GetImag() const
{
    return imag_;
}

bool ReadComplexArray(const char* fileName, Complex*& array, int& count)
{
    ifstream file(fileName);
    if (!file.is_open())
        return false;

    file >> count;
    if (!file || count <= 0)
        return false;

    array = new Complex[count];
    for (Complex* p = array; p < array + count; p++)
        p->Read(file);

    return true;
}

Complex SumArray(const Complex* array, int count)
{
    Complex total;
    for (const Complex* p = array; p < array + count; p++)
        total = total.Add(*p);
    return total;
}

void PrintArray(const Complex* array, int count)
{
    for (const Complex* p = array; p < array + count; p++)
    {
        p->Print();
        cout << endl;
    }
}