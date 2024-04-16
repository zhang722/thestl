#include "string.hpp"

namespace thestl {
string::string(size_t count, element_type ch) {
    data_ = new char[count + 1];
    std::fill_n(data_, count, ch);
    data_[count] = '\0';
    size_ = count + 1;
    cap_ = count + 1;
}

string::string(const string::element_type* s) {
    int len = strlen(s);
    data_ = new char[len + 1];

    memcpy(data_, s, len);
    data_[len] = '\0';
    size_ = len + 1;
    cap_ = len + 1;
}

string::string(const string& other) {
    data_ = new char[other.cap_];
    size_ = other.size_;
    cap_ = other.cap_;
    memcpy(data_, other.data_, size_);
}

string::string(string&& other) noexcept {
    data_ = other.data_;
    size_ = other.size_;
    cap_ = other.cap_;
    other.data_ = nullptr;
}

string::string(iterator first, iterator last) {
    int len = last - first + 1;
    data_ = new char[len];

    for (iterator it = data_, it2 = first; 
        it != data_ + len - 1, it2 != last; it++, it2++) {
        *it = *it2;
    }
    data_[len - 1] = '\0';

    size_ = len;
    cap_ = len;
}

string::~string() {
    if (data_) {
        delete[] data_;
    }
}

string& string::operator=(const string& other) {
    string tmp(other);
    std::swap(tmp.data_, data_);
    std::swap(tmp.size_, size_);
    std::swap(tmp.cap_, cap_);

    return *this;
}

string& string::operator=(string&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        cap_ = other.cap_;
        other.data_ = nullptr;
    }
    return *this;
}

string::element_type& string::operator[](size_t pos) const {
    return data_[pos];
}

string::element_type& string::front() const {
    return data_[0];
}

string::element_type& string::back() const {
    return data_[size_ - 2];
}

string::iterator string::begin() const { 
    return data_; 
}

string::iterator string::end() const {
    return data_ + size_ - 1; 
}

string::element_type* string::data() const { 
    return data_; 
}

bool string::empty() const {
    return size_ == 1; 
}

size_t string::size() const {
    return size_ - 1; 
}

size_t string::length() const { 
    return size(); 
}

size_t string::capacity() const {
    return cap_ - 1;
}

void string::clear() {
    size_ = 1;
    data_[size_ - 1] = '\0';
}

void string::push_back(string::element_type ch) {
    if (size_ == cap_) {
        reserve();
    }
    data_[size_ - 1] = ch;
    size_++;
    data_[size_ - 1] = '\0';
}

void string::pop_back() {
    if (size_ == 1) return;
    size_--;
    data_[size_ - 1] = '\0';
}

string& string::operator+=(const string& other) {
    for (int i = 0; i < other.length(); i++) {
        push_back(other[i]);
    }
    return *this;
}

string& string::operator+=(element_type ch) {
    push_back(ch);

    return *this;
}

string& string::operator+=(const element_type* s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        push_back(s[i]);
    }
    return *this;
}

string string::substr(size_t pos, size_t len) const {
    return string(data_ + pos, data_ + pos + len); 
}

void string::reserve() {
    cap_ = cap_ < 8 ? 8 : cap_ * 2;
    iterator new_data = new string::element_type[cap_];
    memcpy(new_data, data_, size_);
    delete[] data_;
    data_ = new_data;
}

bool operator==(const string& lhs, const string& rhs) {
    if (lhs.length() != rhs.length()) return false;
    for (int i = 0; i < lhs.length(); i++) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true; 
}

bool operator==(const string::element_type* lhs, const string& rhs) {
    return string(lhs) == rhs;
}

bool operator==(const string& lhs, const string::element_type* rhs) {
    return lhs == string(rhs);
}

std::ostream& operator<<(std::ostream& os, const string& s) {
    for (int i = 0; i < s.length(); i++) {
        os << s[i];
    }
    return os;
}

}  // namespace thestl