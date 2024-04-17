#include <bitset>

#include "bitset.hpp"

namespace test {

void bitset_test() {
    std::cout << "Run test : bitset_test" << std::endl;
    thestl::bitset<10> a(0x01);
    std::bitset<10> b(0x01);
    assert(a == b);
    {
        thestl::bitset<10> c(a);
        assert(c == a);
    }
    {
        thestl::bitset<1000> c(0x01);
        std::bitset<1000> d(0x01);
        assert(c == d);

        c.set(90);
        d.set(90);
        assert(c == d);

        c.reset(90);
        d.reset(90);
        assert(c == d);

        c.flip();
        d.flip();
        assert(c == d);

        assert(c.size() == d.size());
        assert(c.count() == d.count());
        assert(c.all() == d.all());
        assert(c.any() == d.any());
        assert(c.none() == d.none());

        c &= 0xffULL;
        d &= 0xffULL;
        assert(c == d);

        c |= 0xffULL;
        d |= 0xffULL;
        assert(c == d);

        c ^= 0xffULL;
        d ^= 0xffULL;
        assert(c == d);
        assert(~c == ~d);

        c <<= 100;
        d <<= 100;
        assert(c == d);

        c >>= 100;
        d >>= 100;
        assert(c == d);
        assert(c << 100 == d << 100);
    }
    std::cout << "Pass test : bitset_test" << std::endl;
}

} // test