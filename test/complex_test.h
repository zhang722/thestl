#include <cassert>
#include <iostream>

#include "complex.hpp"

namespace test {

void complex_test() {
    std::cout << "Run test : complex_test" << std::endl;
    thestl::Complex<int> a(1, 2);
    assert(a.real() == 1);
    assert(a.imag() == 2);
    thestl::Complex b(a);
    assert(b.real() == 1);
    assert(b.imag() == 2);

    // std::cout << a;
    // std::cout << b;
    assert(a == b);
    // std::cout << a + b;
    // std::cout << a + b;
    // std::cout << a * b;
    // std::cout << a / b;
    thestl::Complex<int> c(1, 3);
    assert(a != c);
    std::cout << "Pass test : complex_test" << std::endl;
    std::cout << std::endl;
}

}