#ifndef STRING_HPP_
#define STRING_HPP_

#include <cstddef>
#include <algorithm>
#include <cstring>
#include <iostream>

namespace thestl {

using std::size_t;

class string {
public:
    typedef char element_type;
    typedef char* iterator;

private:
    iterator data_;
    size_t size_;
    size_t cap_;
public:
    string(size_t count, element_type ch);
    string(const element_type* s);
    string(const string& other);
    string(string&& other) noexcept;
    string(iterator first, iterator last);
    ~string();

    string& operator=(const string& other);
    string& operator=(string&& other) noexcept;

    element_type& operator[](size_t pos) const;
    element_type& front() const;
    element_type& back() const;
    iterator begin() const;
    iterator end() const;
    element_type* data() const; 

    bool empty() const;
    size_t size() const;
    size_t length() const;
    size_t capacity() const;

    void clear();
    void push_back(element_type ch);
    void pop_back();

    string& operator+=(const string& other);
    string& operator+=(element_type ch);
    string& operator+=(const element_type* s);    

    string substr(size_t pos, size_t len) const;

    friend std::ostream& operator<<(std::ostream& os, const string& s);
private:
    void reserve();
};

bool operator==(const string& lhs, const string& rhs);
bool operator==(const string::element_type* lhs, const string& rhs);
bool operator==(const string& lhs, const string::element_type* rhs);


} // thestl

#endif