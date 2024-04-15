#ifndef SHARED_PTR_TEST_H_
#define SHARED_PTR_TEST_H_

#include <iostream>
#include <cassert>

#include "shared_ptr.hpp"
namespace test {
void shared_ptr_test() {
    std::cout << "Run test : shared_ptr_test" << std::endl;
    thestl::shared_ptr<int> a(new int(1));
    {
        thestl::shared_ptr b(a);
        assert(b.use_count() == 2);
        assert(a.use_count() == 2);
    }
    {
        thestl::shared_ptr c = a;
        assert(c.use_count() == 2);
        assert(a.use_count() == 2);
    }
    {
        thestl::shared_ptr<int> d(new int(3));
        thestl::shared_ptr<int> e(new int(4));
        thestl::shared_ptr f = e;
        d.swap(e);
        assert(d.use_count() == 2);
        assert(e.use_count() == 1);
        assert(*d == 4);
        assert(*e == 3);
    }
    {
        thestl::shared_ptr<int> b(new int(10));
        thestl::weak_ptr<int> c(b);
        if (!c.expired()) {
            thestl::shared_ptr d = c.lock();
            assert(*d == 10);
        }
        assert(b.use_count() == 1);
    }
    assert(a.use_count() == 1);
    assert(*a == 1);

    std::cout << "Pass test : shared_ptr_test" << std::endl;
    std::cout << std::endl;
}

} // test

#endif