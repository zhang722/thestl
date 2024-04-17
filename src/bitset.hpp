#ifndef BITSET_HPP_
#define BITSET_HPP_

#include <cstring>
#include <iostream>
#include <bitset>

#include "string.hpp"

namespace thestl {

/*
 *  [0 ... 63] [64 ... 127] [128 ... 191] [192 ... 255]
 *  map: n --> idx of n / W, pos of W - 1 - n % W
 */
template <size_t N>
class bitset {
    typedef unsigned long long data_type;

    static constexpr size_t W = sizeof(data_type) * 8;
    static constexpr size_t L = (N + W - 1) / W;
    data_type data_[L];
public:
    bitset();
    bitset(unsigned long val);
    bitset(string& str);
    bitset(const bitset& other);
    ~bitset() {}

    bitset& operator=(const bitset& other) = delete;

    bool operator[](size_t pos) const;
    size_t size() const;
    size_t count();
    bool all();
    bool any();
    bool none();
    
    bitset& set(size_t pos);
    bitset& reset(size_t pos);
    bitset& flip();

    bitset& operator&=(const bitset& other);
    bitset& operator|=(const bitset& other);
    bitset& operator^=(const bitset& other);
    bitset operator~();

    bitset& operator<<=(size_t pos);
    bitset& operator>>=(size_t pos);
    bitset operator<<(size_t pos);
    bitset operator>>(size_t pos);

    template <size_t M>
    friend std::ostream& operator<<(std::ostream& os, const bitset<M>& b);
};

unsigned long long reverse(unsigned long long x)
{
	x = (((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1));
	x = (((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2));
	x = (((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4));
	x = (((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8));
	x = (((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16));
	return((x >> 32) | (x << 32));
}

// template <size_t N>
// bitset<N>& operator&(const bitset<N>& lhs, const bitset<N>& rhs);

// template <size_t N>
// bitset<N>& operator|(const bitset<N>& lhs, const bitset<N>& rhs);

// template <size_t N>
// bitset<N>& operator^(const bitset<N>& lhs, const bitset<N>& rhs);

template <size_t N>
inline bitset<N>::bitset() {
    memset(data_, 0, L * 8);
}

template <size_t N>
inline bitset<N>::bitset(unsigned long val) {
    memset(data_, 0, L * 8);
    data_[0] = reverse(val);
}

template <size_t N>
inline bitset<N>::bitset(string& str) {
    int n = str.length();

    for (int i = n - 1; i >= 0; i--) {
        if (str[i] == '0') set(n-i-1);
        else reset(n-i-1);
    }
}

template <size_t N>
inline bitset<N>::bitset(const bitset& other) {
    memcpy(data_, other.data_, L * 8);
}

template <size_t N>
inline bool bitset<N>::operator[](size_t pos) const {
//  map: n --> idx of n / W, pos of W - 1 - n % W
    data_type a = data_[pos / W];
    data_type b = data_type(0x01) << (W - 1 - pos % W);
    data_type c = a & b;
    return (a & b) != 0;
}

template <size_t N>
inline size_t bitset<N>::size() const {
  return N;
}

template <size_t N>
inline size_t bitset<N>::count() {
    int cnt = 0;
    for (int i = 0; i < L; i++) {
        data_type t = data_[i];
        while (t != 0) {
            t = t & (t - 1);
            cnt++;
        }
    }
    return cnt;
}

template <size_t N>
inline bool bitset<N>::all() {
    for (int i = 0; i < L; i++) {
        if (data_[i] ^ 0xffffffffffffffff != 0) return false;
    }
    return true;
}

template <size_t N>
inline bool bitset<N>::any() {
    for (int i = 0; i < L; i++) {
        if (data_[i] != 0) return true;
    }
    return false;
}

template <size_t N>
inline bool bitset<N>::none() {
  return !any();
}

template <size_t N>
inline bitset<N>& bitset<N>::set(size_t pos) {
    data_type tmp = data_[pos / W];
    data_[pos / W] = tmp | (data_type(0x01) << (W - 1 - pos % W));
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::reset(size_t pos) {
    data_type tmp = data_[pos / W];
    data_[pos / W] = tmp & ~(data_type(0x01) << (W - 1 - pos % W));
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::flip() {
    for (int i = 0; i < L; i++) {
        data_[i] = ~data_[i];
    } 
    for (int i = N; i < L*W; i++) {
        reset(i);
    }
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::operator&=(const bitset& other) {
    for (int i = 0; i < L; i++) {
        data_[i] &= other.data_[i];
    }
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::operator|=(const bitset& other) {
    for (int i = 0; i < L; i++) {
        data_[i] |= other.data_[i];
    }
    for (int i = N; i < L*W; i++) {
        reset(i);
    }
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::operator^=(const bitset& other) {
    for (int i = 0; i < L; i++) {
        data_[i] ^= other.data_[i];
    }
    for (int i = N; i < L*W; i++) {
        reset(i);
    }
    return *this;
}

template <size_t N>
inline bitset<N> bitset<N>::operator~() {
    bitset<N> ret(*this);
    ret.flip();
    return ret;
}

template <size_t N>
inline bitset<N>& bitset<N>::operator<<=(size_t pos) {
    int n = size();
    for (int i = n - 1; i >= pos; i--) {
        if (this->operator[](i - pos)) set(i);
        else reset(i);
    }
    for (int i = 0; i < pos; i++) {
        reset(i);
    }
    return *this;
}

template <size_t N>
inline bitset<N>& bitset<N>::operator>>=(size_t pos) {
    int n = size();
    for (int i = 0; i < n - pos; i++) {
        if (this->operator[](i + pos)) set(i);
        else reset(i);
    }
    for (int i = n - pos; i < n; i++) {
        reset(i);
    }
    return *this;
}

template <size_t N>
inline bitset<N> bitset<N>::operator<<(size_t pos) {
    bitset<N> ret(*this);
    ret <<= pos;
    return ret;
}

template <size_t N>
inline bitset<N> bitset<N>::operator>>(size_t pos) {
    bitset<N> ret(*this);
    ret >>= pos;
    return ret;
}

template <size_t M>
std::ostream& operator<<(std::ostream& os, const bitset<M>& b) {
    int n = b.size();
    for (int i = n - 1; i >= 0; i--) {
        os << (int)b[i];
    }
    return os;
}

template <size_t N>
bool operator==(const bitset<N>& lhs, const std::bitset<N>& rhs) {
    int n = lhs.size();
    for (int i = 0; i < n; i++) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template <size_t N>
bool operator==(const std::bitset<N>& lhs, const bitset<N>& rhs) {
    int n = lhs.size();
    for (int i = 0; i < n; i++) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template <size_t N>
bool operator==(const bitset<N>& lhs, const bitset<N>& rhs) {
    int n = lhs.size();
    for (int i = 0; i < n; i++) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

// template <size_t N>
// bitset<N>& operator!=(const bitset<N>& lhs, const std::bitset<N>& rhs) {
//     return !(lhs == rhs);
// }

// template <size_t N>
// bitset<N>& operator==(const std::bitset<N>& lhs, const bitset<N>& rhs) {
//     int n = lhs.size();
//     for (int i = 0; i < n; i++) {
//         if (lhs[i] != rhs[i]) return false;
//     }
//     return true;
// }

// template <size_t N>
// bitset<N>& operator==(const bitset<N>& lhs, const bitset<N>& rhs) {
//     int n = lhs.size();
//     for (int i = 0; i < n; i++) {
//         if (lhs[i] != rhs[i]) return false;
//     }
//     return true;
// }

}  // namespace thestl

#endif