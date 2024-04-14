
namespace thestl {

class Deleter {
public:
    Deleter() = default;

    template <typename U>
    void operator()(U *p) noexcept {
        if (p) {
            delete p;
        }
    }
};

template <typename T, typename U = Deleter>
class unique_ptr {
    T *ptr;
    U deleter;
public:
    explicit unique_ptr();
    explicit unique_ptr(T *p);
    explicit unique_ptr(unique_ptr&& other);
    unique_ptr& operator=(unique_ptr&& other);
    ~unique_ptr();

    unique_ptr(const unique_ptr& p) = delete;
    void operator=(const unique_ptr& other) = delete;
    void operator=(T* p) = delete;

    T* release() noexcept;
    void reset(T *p) noexcept;
    void swap(unique_ptr& other) noexcept;
    T* get() const noexcept;
    U get_deleter() const noexcept;
    explicit operator bool() const noexcept;

    T& operator *();
    T* operator ->();
};

template <typename T, typename U>
unique_ptr<T, U>::unique_ptr() {
    ptr = nullptr;
}

template <typename T, typename U>
unique_ptr<T, U>::unique_ptr(T *p) {
    ptr = p;
}

template <typename T, typename U>
unique_ptr<T, U>::~unique_ptr() {
    if(ptr) {
        deleter(ptr);
    }
    ptr = nullptr;
}

template <typename T, typename U>
unique_ptr<T, U>::unique_ptr(unique_ptr&& other) {
    ptr = other.ptr;
    deleter = other.deleter;
    other.ptr = nullptr;
}

template <typename T, typename U>
unique_ptr<T, U>& unique_ptr<T, U>::operator=(unique_ptr&& other) {
    if (other == &this) return *this;

    ptr = other.ptr;
    deleter = other.ptr;
    other.ptr = nullptr;

    return *this;
}

template <typename T, typename U>
T* unique_ptr<T, U>::release() noexcept {
    T *p = ptr;
    ptr = nullptr;
    return p;
}

template <typename T, typename U>
void unique_ptr<T, U>::reset(T* p) noexcept {
    if (ptr) {
        deleter(ptr);
    }
    ptr = p;
}

template <typename T, typename U>
void unique_ptr<T, U>::swap(unique_ptr& other) noexcept {
    std::swap(ptr, other.ptr);
    std::swap(deleter, other.deleter);
}

template <typename T, typename U>
T* unique_ptr<T, U>::get() const noexcept {
    return ptr;
}

template <typename T, typename U>
U unique_ptr<T, U>::get_deleter() const noexcept {
    return deleter;
}

template <typename T, typename U>
unique_ptr<T, U>::operator bool() const noexcept {
    if (ptr) {
        return true;
    } else {
        return false;
    }
}

template <typename T, typename U>
T& unique_ptr<T, U>::operator *() {
    return *ptr;
}

template <typename T, typename U>
T* unique_ptr<T, U>::operator ->() {
    return ptr;
}
} // thestl