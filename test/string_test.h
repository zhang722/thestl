#include <iostream>
#include <cassert>

#include "string.hpp"

namespace test {

void string_test() {
    std::cout << "Run test : string_test" << std::endl;

    thestl::string a("abc");
    assert(a[0] == 'a');
    assert(a[1] == 'b');
    assert(a[2] == 'c');
    assert(a.front() == 'a');
    assert(a.back() == 'c');
    assert(*a.begin() == 'a');
    assert(a.length() == 3);
    assert(a.size() == 3);
    thestl::string b(a);
    assert(b.length() == 3);
    assert(a == b);
    thestl::string c(3, 'a');
    assert(c == "aaa");

    a.push_back('d');
    assert(a == "abcd");
    assert(a.length() == 4);
    a.pop_back();
    assert(a.length() == 3);
    {
        thestl::string e("a");
        assert(e == "a");
        e += "bc";
        assert(e == "abc");
    }

    {
        thestl::string d = a;
        assert(d.length() == 3);
        assert(d == a);
        thestl::string e = std::move(d);
        assert(e.length() == 3);
        assert(e == a);
        e.clear();
        assert(e.length() == 0);
        assert(e == "");
        e += thestl::string("efg");
        assert(e == "efg");
        e += 'h';
        assert(e == "efgh");
        e += a;
        assert(e == "efghabc");
        assert(e.substr(0, 3) == "efg");
    }

    std::cout << "Pass test : string_test" << std::endl;
    std::cout << std::endl;
}

} // test