// Complex operator:
// +-*/ another complex
// +-*/ T
// ==, !=,
// <<, >>,
// getter

#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <iostream>

namespace thestl {

using std::ostream;
using std::istream;

template <typename T>
class Complex {
    T r;
    T i;
public:
    // constructor
    Complex() : r(0), i(0) {}
    explicit Complex(T r_, T i_) : r(r_), i(i_) {}

    Complex(const Complex& other);
    Complex& operator=(const Complex& other);
    
    Complex& operator+(const Complex& other);
    Complex& operator-(const Complex& other);
    Complex& operator*(const Complex& other);
    Complex& operator/(const Complex& other);
    bool operator==(const Complex& other);
    bool operator!=(const Complex& other);

    T real() {return r;};
    T imag() {return i;};

    template <typename U>
    friend ostream& operator<<(ostream& os, const Complex<U>& c);
    template <typename U>
    friend istream& operator>>(istream& is, const Complex<U>& c);
};

template <typename T>
Complex<T>::Complex(const Complex& other) {
    r = other.r;
    i = other.i;
}

template <typename T>
Complex<T>& Complex<T>::operator=(const Complex& other) {
    r = other.r;
    i = other.i;

    return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator+(const Complex& other) {
    r += other.r;
    i += other.i;

    return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator-(const Complex& other) {
    r -= other.r;
    i -= other.i;

    return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator*(const Complex& other) {
    T tempr = r * other.r - i * other.i;
    T tempi = r * other.i + i * other.r;
    r = tempr;
    i = tempi;

    return *this;
}

template <typename T>
Complex<T>& Complex<T>::operator/(const Complex& other) {
    T tempr = (r * other.r + i * other.i) / (other.r * other.r + other.i * other.i);
    T tempi = (i * other.r - r * other.i) / (other.r * other.r + other.i * other.i);
    r = tempr;
    i = tempi;

    return *this;
}

template <typename T>
bool Complex<T>::operator==(const Complex& other) {
    return r == other.r && i == other.i;
}

template <typename T>
bool Complex<T>::operator!=(const Complex& other) {
    return r != other.r || i != other.i;
}



template <typename U>
ostream& operator<<(ostream& os, const Complex<U>& c) {
    os << c.r << ',' << c.i << std::endl;
    return os;
}

template <typename U>
istream& operator>>(istream& is, const Complex<U>& c) {
    is >> c.r >> c.i;
    return is;
}

} // thestl
#endif