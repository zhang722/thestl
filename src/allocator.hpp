#include <memory>
#include <iterator>

namespace thestl {

template <typename T>
class allocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* iterator;
public:
    T* allocate();
    T* allocate(size_type n);

    void deallocate(T* p);
    void deallocate(T* p, size_type n);

    void construct(T* p);
    void construct(T* p, const T& x);
    
    template <typename... Args>
    void construct(T* p, Args&& ...args);

    void destroy(T* p);
    void destroy(T* first, T* last);
};

template <typename T>
inline T* allocator<T>::allocate() {
    return static_cast<T*>(::operator new(sizeof(T)));
}

template <typename T>
inline T* allocator<T>::allocate(size_type n) {
    return static_cast<T*>(::operator new(sizeof(T) * n));
}

template <typename T>
inline void allocator<T>::deallocate(T* p) {
    if (p == nullptr) return;

    ::operator delete(p);
}

template <typename T>
inline void allocator<T>::deallocate(T* p, size_type n) {
    if (p == nullptr) return;

    ::operator delete(p);
}

template <typename T>
inline void allocator<T>::construct(T* p) {
    if (p == nullptr) return;

    ::new (static_cast<void*>(p)) T();
}

template <typename T>
inline void allocator<T>::construct(T* p, const T& x) {
    if (p == nullptr) return;

    ::new (static_cast<void*>(p)) T(x);
}



template <typename T>
template <typename... Args>
inline void allocator<T>::construct(T* p, Args&&... args) {
    if (p == nullptr) return;

    ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
}

template <typename T>
inline void allocator<T>::destroy(T* p) {
    thestl::destroy(p);
}

template <typename T>
inline void allocator<T>::destroy(T* first, T* last) { 
    thestl::destroy(first, last);
}

template <typename T>
void destroy(T * p) {
    destroy_one(p, std::is_trivially_destructible<T>{});
}

template <typename T>
void destroy_one(T* p, std::true_type) {}

template <typename T>
void destroy_one(T* p, std::false_type) {
    if (p == nullptr) return;
    p->~T();
}

template <typename Iterator>
void destroy(Iterator first, Iterator last) {
    destroy_cat(first, last, std::is_trivially_destructible<
        typename std::iterator<Iterator>::value_type>{});
}

template <typename Iterator>
void destroy_cat(Iterator first, Iterator last, std::true_type) {}

template <typename Iterator>
void destroy_cat(Iterator first, Iterator last, std::false_type) {
    for (; first != last; ++first) {
        destroy(first);
    }
}

}  // namespace thestl