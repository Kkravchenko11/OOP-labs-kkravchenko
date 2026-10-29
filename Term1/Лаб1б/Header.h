class Complex
{
private:
    int r;
    int m;
public:
    void init(int x, int y);
    void addInt(int x, int y);
    Complex add(Complex c);
    void print();
};