#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

class Complex
{
public:
    Complex();
    Complex(double real, double imag);

    void Init(double real, double imag);
    void AddToParts(int addReal, int addImag);
    Complex Add(const Complex& other) const;
    void Print() const;
    void Read(istream& in);

    double GetReal() const;
    double GetImag() const;

private:
    double real_;
    double imag_;
};

bool ReadComplexArray(const char* fileName, Complex*& array, int& count);
Complex SumArray(const Complex* array, int count);
void PrintArray(const Complex* array, int count);