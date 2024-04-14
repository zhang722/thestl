#ifndef UNIQUE_PTR_H_
#define UNIQUE_PTR_H_

#include <iostream>
#include <cassert>
#include <unique_ptr.hpp>

namespace test {

void unique_ptr_test() {
    std::cout << "Run test : unique_ptr_test" << std::endl;

    thestl::unique_ptr<int> a(new int(1));
    assert(*a == 1);
    thestl::unique_ptr<int> b(std::move(a));
    assert(a.get() == nullptr);
    assert(*b == 1);

    int* p = b.release();
    assert(*p == 1);
    assert(b.get() == nullptr);
    
    b.reset(p);
    assert(b.get() == p);
    std::cout << "Pass test : unique_ptr_test" << std::endl;
    std::cout << std::endl;
}

} // test

#endif 