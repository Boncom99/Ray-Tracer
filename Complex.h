#ifndef COMPLEX_H
#define COMPLEX_H
#include <math.h>
class Complex
{
public:
    double r;
    double i;
    Complex();
    Complex(double r, double i);
    void conjugate();
    double modul() const;
    double modulSq() const;
    Complex &operator+=(const Complex &c)
    {
        r += c.r;
        i += c.i;
        return *this;
    }
    Complex &operator*=(const Complex &c)
    {
        r = r * c.r - i * c.i;
        i = r * c.i + i * c.r;
        return *this;
    }
};

Complex::Complex()
{
}

Complex::Complex(double r, double i) : r(r), i(i)
{
}
void Complex::conjugate()
{
    i *= -1;
}
double Complex::modul() const
{
    return sqrt(r * r + i * i);
}
double Complex::modulSq() const
{
    return r * r + i * i;
}
inline Complex operator+(const Complex &c1, const Complex &c2)
{
    return Complex(c1.r + c2.r, c1.i + c2.i);
}
inline Complex operator+(const double &d, const Complex &c)
{
    return Complex(c.r + d, c.i);
}
inline Complex operator+(const Complex &c, const double &d)
{
    return Complex(c.r + d, c.i);
}
inline Complex operator*(double d, const Complex &c)
{
    return Complex(c.r * d, c.i * d);
}
inline Complex operator*(const Complex &c, double d)
{
    return Complex(c.r * d, c.i * d);
}
inline Complex operator*(const Complex &c1, const Complex &c2)
{
    return Complex(c1.r * c2.r - c1.i * c2.i, c1.r * c2.i + c1.i * c2.r);
}
inline Complex operator/(double d, const Complex &c)
{
    double mod = c.modulSq();
    return Complex(c.r * d / mod, -c.i * d / mod);
}
inline Complex operator/(const Complex &c, double d)
{
    return Complex(c.r / d, c.i / d);
}
inline Complex operator/(const Complex &c1, const Complex &c2)
{
    Complex conj = c2;
    conj.conjugate();
    double mod = c2.modulSq();
    Complex aux = c1 * conj;
    return aux / mod;
}
#endif