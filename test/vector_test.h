#ifndef VECTOR_TEST_H_
#define VECTOR_TEST_H_

#include <iostream>
#include <cassert>

#include "vector.hpp"

namespace test {
void vector_test() {
    std::cout << "Run test : vector_test" << std::endl;
    thestl::vector<int> a;    
    assert(a.size() == 0);
    assert(a.capacity() == 8);

    a.push_back(1);
    a.push_back(2);
    assert(a.size() == 2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    assert(a.size() == 9);
    assert(a.capacity() == 16);
    assert(a[0] == 1);
    assert(a.front() == 1);
    assert(a.back() == 2);
    assert(*a.begin() == 1);
    assert((*(a.end()-1)) == 2);
    a.pop_back();
    assert(a.size() == 8);

    thestl::vector<int> b(2, 0);
    thestl::vector<int> c(b);
    assert(b == c);
    c.pop_back();
    c.pop_back();
    assert(c.empty());
    assert(!b.empty());

    thestl::vector<int> d(2, 0);
    thestl::vector<int> e(std::move(d));
    assert(e.size() == 2);
    assert(e.capacity() == 2);
    assert(d.size() == 0);
    assert(d.capacity() == 0);
    e.emplace_back(2);
    assert(e.size() == 3);
    assert(e.back() == 2);

    std::cout << "Pass test : vector_test" << std::endl;
    std::cout << std::endl;
}

} // test

#endif