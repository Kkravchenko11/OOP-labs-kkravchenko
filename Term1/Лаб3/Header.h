#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;

class B1 {
    int b1;
public:
    B1(int v);
    virtual ~B1();
    virtual void show(ostream& os = cout) const;
    friend ostream& operator<<(ostream& os, const B1& obj);
};

class B2 {
    int b2;
public:
    B2(int v);
    virtual ~B2();
    virtual void show(ostream& os = cout) const;
    friend ostream& operator<<(ostream& os, const B2& obj);
};

class B3 {
    int b3;
public:
    B3(int v);
    virtual ~B3();
    virtual void show(ostream& os = cout) const;
    friend ostream& operator<<(ostream& os, const B3& obj);
};

class D1 : private B1, public B2, protected virtual B3 {
    int d1;
public:
    D1(int vb1, int vb2, int vb3, int v);
    void show(ostream& os = cout) const override;
    friend ostream& operator<<(ostream& os, const D1& obj);
};

class D3 : public virtual B3 {
    int d3;
public:
    D3(int vb3, int v);
    void show(ostream& os = cout) const override;
    friend ostream& operator<<(ostream& os, const D3& obj);
};

class D2 : public D1, private D3 {
    int d2;
public:
    D2(int vb1, int vb2, int vb3, int vd1, int vd3, int v);
    void show(ostream& os = cout) const override;
    friend ostream& operator<<(ostream& os, const D2& obj);
};

class D4 : protected D2 {
    int d4;
public:
    D4(int vb1, int vb2, int vb3, int vd1, int vd3, int vd2, int v);
    void show(ostream& os = cout) const override;
    friend ostream& operator<<(ostream& os, const D4& obj);
};

#endif#pragma once
