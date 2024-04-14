#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace thestl {

template <typename T>
class vector {
    typedef T element_type;
    typedef T* iterator;
    typedef T* pointer;
    typedef T& reference;

    iterator start;
    iterator finish;
    iterator end_of_storage;
public:
    vector();
    vector(size_t n, const element_type& value);
    vector(const vector& other);
    vector(vector&& other);
    vector& operator=(const vector& other);
    vector& operator=(vector&& other);
    ~vector() {delete[] start;}

    reference operator[](size_t idx);
    bool operator==(const vector& other);

    void push_back(const element_type& val);
    void push_back(element_type&& val);

    template <typename... Args>
    void emplace_back(Args&&... val);

    void pop_back();

    reference front();
    reference back();
    iterator begin();
    iterator end();
    size_t size() const;
    size_t capacity();
    bool empty();
private:
    void reserve();
};

template <typename T>
vector<T>::vector() {
    start = new element_type[8];
    finish = start;
    end_of_storage = finish + 8;
}

template <typename T>
vector<T>::vector(size_t n, const element_type& value) {
    start = new element_type[n];
    finish = start + n;
    end_of_storage = finish;
}

template <typename T>
vector<T>::vector(const vector& other) {
    int n = other.size();
    start = new element_type[n];
    finish = start + n;
    end_of_storage = finish;
    for (iterator it = start, it2 = other.start; 
        it != finish, it2 != other.finish; it++, it2++) {
        *it = *it2;
    }
}

template <typename T>
vector<T>::vector(vector&& other) {
    start = other.start;
    finish = other.finish;
    end_of_storage = other.end_of_storage;
    other.start = other.finish = other.end_of_storage = nullptr;    
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    int n = other.size();
    start = new element_type[n];
    finish = start + n;
    end_of_storage = finish;
    for (iterator it = start, it2 = other.start; 
        it != finish, it2 != other.finish; it++, it2++) {
        *it = *it2;
    }   
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) {
    start = other.start;
    finish = other.finish;
    end_of_storage = other.end_of_storage;
    other.start = other.finish = other.end_of_storage = nullptr;    

    return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_t idx) {
    return *(start + idx);
}


template <typename T>
bool vector<T>::operator==(const vector& other) {
    for (iterator it = start, it2 = other.start; 
        it != finish, it2 != other.finish; it++, it2++) {
        if (*it != *it2) return false;
    }
    return true;
}


template <typename T>
void vector<T>::push_back(const element_type& val) {
    if (finish == end_of_storage) {
        reserve();
    }
    *finish = val;
    finish++;
}

template <typename T>
void vector<T>::push_back(element_type&& val) {
    if (finish == end_of_storage) {
        reserve();
    }
    *finish = std::forward<element_type>(val);
    finish++;
}

template <typename T>
void vector<T>::pop_back() {
    if (finish != start) {
        finish--;
        finish->~element_type();
    }
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
    return *start;
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return *(finish - 1);
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return start;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return finish - 1;
}

template <typename T>
inline size_t vector<T>::size() const {
  return finish - start;
}

template <typename T>
inline size_t vector<T>::capacity() {
  return end_of_storage - start;
}

template <typename T>
inline bool vector<T>::empty() {
  return finish == start;
}

template <typename T>
void vector<T>::reserve() {
    int cap = end_of_storage - start;
    int size = finish - start;
    if (cap < 4) cap = 4; 

    iterator new_start = new element_type[cap * 2];
    // copy
    for (iterator it = start, it2 = new_start; it != finish; it++, it2++) {
        *it2 = *it;
    }
    delete[] start;
    start = new_start;
    finish = start + size;
    end_of_storage = start + cap * 2;
}

template <typename T>
template <typename... Args>
inline void vector<T>::emplace_back(Args&&... val) {
    if (finish == end_of_storage) {
        reserve();
    }

    *finish = element_type(std::forward<Args>(val)...);
    finish++;
}

}  // namespace thestl
#endif
