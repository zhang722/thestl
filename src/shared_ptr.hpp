#include <algorithm>

namespace thestl {
class ref_count {
    long uses_;
    long weaks_;
public:
    ref_count() : uses_(1), weaks_(1) {}
    ref_count(long uses, long weaks) : uses_(uses), weaks_(weaks) {}
    ~ref_count() = default;

    long incre_ref();
    long decre_ref();
    long incre_wref();
    long decre_wref();
    inline long ref();
    inline long wref();
};

long ref_count::incre_ref() {
    return ++uses_;
}

long ref_count::decre_ref() {
    return --uses_;
}

long ref_count::incre_wref() {
    return ++weaks_;
}

long ref_count::decre_wref() {
    return --weaks_;
}

long ref_count::ref() {
    return uses_;
}

long ref_count::wref() {
    return weaks_;
}

template <typename U>
class weak_ptr;

template <typename T>
class shared_ptr {
    typedef T element_type;
    typedef T& reference;
    
    element_type* ptr_;
    ref_count* rep_;

    template <typename U>
    friend class weak_ptr;
public:
    shared_ptr() : ptr_(nullptr), rep_(nullptr) {}
    shared_ptr(std::nullptr_t) : ptr_(nullptr), rep_(nullptr) {}
    shared_ptr(element_type* ptr, ref_count* rep_);
    shared_ptr(element_type* ptr);
    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other) noexcept;
    ~shared_ptr();

    shared_ptr& operator =(const shared_ptr& other); 
    shared_ptr& operator =(shared_ptr&& other) noexcept; 

    void reset(element_type* ptr);
    void swap(shared_ptr& other);

    element_type* get() const;
    reference operator*() const;
    element_type* operator->() const;
    long use_count() const;
    explicit operator bool() const;

};

template <typename T>
inline shared_ptr<T>::shared_ptr(element_type* ptr, ref_count* rep) {
    ptr_ = ptr;
    rep_ = rep;
    if (rep_) {
        rep_->incre_ref();
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(typename shared_ptr<T>::element_type* ptr) {
  rep_ = new ref_count();
  ptr_ = ptr;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(const shared_ptr& other) {
    rep_ = other.rep_;
    if (rep_) {
        rep_->incre_ref();
    }
    ptr_ = other.ptr_;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    rep_ = other.rep_;
    if (rep_) {
        rep_->incre_ref();
    }
    ptr_ = other.ptr_;
}


template <typename T>
inline shared_ptr<T>::~shared_ptr() {
    if (!rep_) return;
    if (rep_->decre_ref() == 0) {
        delete ptr_;
        ptr_ = nullptr;
        if (rep_->decre_wref() == 0) {
            delete rep_;
            rep_ = nullptr;
        }
    }
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator =(const shared_ptr& other) {
    if (this == &other) return *this;

    shared_ptr tmp(other);
    std::swap(rep_, tmp.rep_);
    std::swap(ptr_, tmp.ptr_);

    return *this;
} 

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator =(shared_ptr&& other) noexcept {
    if (this == &other) return *this;

    shared_ptr tmp(other);
    std::swap(rep_, tmp.rep_);
    std::swap(ptr_, tmp.ptr_);

    return *this;
} 

template<typename T>
void shared_ptr<T>::reset(typename shared_ptr<T>::element_type* ptr) {
    shared_ptr<T> tmp(ptr);
    std::swap(rep_, tmp.rep_);
    std::swap(ptr_, tmp.ptr_);
}

template<typename T>
void shared_ptr<T>::swap(shared_ptr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(rep_, other.rep_);
}

template<typename T>
typename shared_ptr<T>::element_type * shared_ptr<T>::get() const {
    return ptr_;
}

template<typename T>
typename shared_ptr<T>::reference shared_ptr<T>::operator*() const {
    return *ptr_;
}

template<typename T>
typename shared_ptr<T>::element_type* shared_ptr<T>::operator->() const {
    return ptr_;
}


template<typename T>
long shared_ptr<T>::use_count() const {
    return rep_->ref();
}

template<typename T>
shared_ptr<T>::operator bool() const {
    return ptr_;
}



template <typename T>
class weak_ptr {
    typedef T element_type;
    typedef T& reference;

    element_type* ptr_;
    ref_count* rep_;
public:
    weak_ptr() : ptr_(nullptr), rep_(nullptr) {}
    explicit weak_ptr(std::nullptr_t) : ptr_(nullptr), rep_(nullptr) {}
    weak_ptr(const weak_ptr& other);
    weak_ptr& operator=(const weak_ptr& other);
    weak_ptr(weak_ptr&& other) noexcept;
    weak_ptr& operator=(weak_ptr&& other) noexcept;
    weak_ptr(const shared_ptr<T>& other);
    ~weak_ptr();

    void reset();
    long use_count() const;
    bool expired() const;
    shared_ptr<T> lock() const;
};

template <typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& other) {
    ptr_ = other.ptr_;
    rep_ = other.rep_;
    if (rep_) {
        rep_->incre_wref();
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator =(const weak_ptr& other) {
    weak_ptr tmp(other);
    std::swap(ptr_, tmp.ptr_);
    std::swap(rep_, tmp.rep_);

    return *this;
}

template <typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    rep_ = other.rep_;
    if (rep_) {
        rep_->incre_wref();
    }
}

template <typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr&& other) noexcept {
    weak_ptr tmp(other);
    std::swap(ptr_, tmp.ptr_);
    std::swap(rep_, tmp.rep_);

    return *this;
}

template <typename T>
inline weak_ptr<T>::weak_ptr(const shared_ptr<T>& other) {
    ptr_ = other.ptr_;
    rep_ = other.rep_;
    if (rep_) {
        rep_->incre_wref();
    }
}

template<typename T>
inline weak_ptr<T>::~weak_ptr() {
    if (rep_->decre_wref() == 0) {
        delete rep_;
        rep_ = nullptr;
    }
}

template<typename T>
void weak_ptr<T>::reset() {
    weak_ptr tmp;
    std::swap(ptr_, tmp.ptr_);
    std::swap(rep_, tmp.rep_);
}

template<typename T>
long weak_ptr<T>::use_count() const {
    return rep_->ref();
}

template<typename T>
bool weak_ptr<T>::expired() const {
    return rep_->ref() == 0;
}

template<typename T>
shared_ptr<T> weak_ptr<T>::lock() const {
    shared_ptr<T> ret(ptr_, rep_);
    return ret;
}

} // thestl