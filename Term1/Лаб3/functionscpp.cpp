#include "header.h"
using namespace std;

B1::B1(int v) : b1(v) {}
B1::~B1() {}
void B1::show(ostream& os) const { os << "B1: b1 = " << b1; }
ostream& operator<<(ostream& os, const B1& obj) {
    obj.show(os);
    return os;
}

B2::B2(int v) : b2(v) {}
B2::~B2() {}
void B2::show(ostream& os) const { os << "B2: b2 = " << b2; }
ostream& operator<<(ostream& os, const B2& obj) {
    obj.show(os);
    return os;
}

B3::B3(int v) : b3(v) {}
B3::~B3() {}
void B3::show(ostream& os) const { os << "B3: b3 = " << b3; }
ostream& operator<<(ostream& os, const B3& obj) {
    obj.show(os);
    return os;
}

D1::D1(int vb1, int vb2, int vb3, int v)
    : B3(vb3), B1(vb1), B2(vb2), d1(v) {
}
void D1::show(ostream& os) const { os << "D1: d1 = " << d1; }
ostream& operator<<(ostream& os, const D1& obj) {
    obj.show(os);
    return os;
}

D3::D3(int vb3, int v) : B3(vb3), d3(v) {}
void D3::show(ostream& os) const { os << "D3: d3 = " << d3; }
ostream& operator<<(ostream& os, const D3& obj) {
    obj.show(os);
    return os;
}

D2::D2(int vb1, int vb2, int vb3, int vd1, int vd3, int v)
    : B3(vb3), D1(vb1, vb2, vb3, vd1), D3(vb3, vd3), d2(v) {
}
void D2::show(ostream& os) const { os << "D2: d2 = " << d2; }
ostream& operator<<(ostream& os, const D2& obj) {
    obj.show(os);
    return os;
}

D4::D4(int vb1, int vb2, int vb3, int vd1, int vd3, int vd2, int v)
    : B3(vb3), D2(vb1, vb2, vb3, vd1, vd3, vd2), d4(v) {
}
void D4::show(ostream& os) const { os << "D4: d4 = " << d4; }
ostream& operator<<(ostream& os, const D4& obj) {
    obj.show(os);
    return os;
}