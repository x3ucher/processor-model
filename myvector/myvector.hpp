#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>
#include <memory>
#include <type_traits>

template<class T>
class MyVector;

template<class T, bool is_const>
class MVIterator {
private:
    using ptr_t = std::conditional_t<is_const, const T, T>*;
    ptr_t value;

    MVIterator(ptr_t ptr) : value(ptr) {};

    friend MyVector<T>;
    friend MVIterator<T, !is_const>;
public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<is_const, const T*, T*>;
    using reference = std::conditional_t<is_const, const T&, T&>;
    using iterator_category = std::bidirectional_iterator_tag;

    MVIterator() noexcept : value(nullptr) {}

    template<bool other_const>
    MVIterator(const MVIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) : value(o.value) {}
    
    template<bool other_const>
    MVIterator& operator = (const MVIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) {
        value = o.value;
        return *this;
    }

    reference operator * () const noexcept {
        return *value;
    }

    pointer operator -> () const noexcept {
        return value;
    }

    template<bool other_const>
    bool operator == (const MVIterator<T, other_const>& o) const noexcept {
        return value == o.value;
    }

    template<bool other_const>
    bool operator != (const MVIterator<T, other_const>& o) const noexcept {
        return !(value != o.value);
    }

    MVIterator& operator ++ () noexcept {
        ++value;
        return *this;
    }

    MVIterator operator ++ (int) noexcept {
        MVIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    MVIterator& operator -- () noexcept {
        --value;
        return *this;
    }

    MVIterator operator -- (int) noexcept {
        MVIterator tmp = *this;
        --(*this);
        return *this;
    }
};

template<class T>
class MyVector {
private:
    T *vector_;
    size_t size_;
    size_t capacity_;
public:
    using iterator = MVIterator<T, false>;
    using const_iterator = MVIterator<T, true>;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

    // constructor
    MyVector() : vector_(nullptr), size_(0), capacity_(0) {}
    explicit MyVector(size_t size) : vector_(new T[size]), size_(size), capacity_(size) {}

    // destructor
    ~MyVector() { 
        delete[] vector_;
        size_ = 0;
        capacity_ = 0;
    }

    // copy constructor
    MyVector(const MyVector<T> &other) : vector_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
        std::copy(other.vector_, other.vector_ + other.size_, vector_);
    }

    // operators
    MyVector<T> &operator=(const MyVector<T> &other) {
        if (this != &other) {
            delete[] vector_;
            size_ = other.size_;
            capacity_ = other.size_;
            vector_ = new T[size_];

            std::copy(other.vector_, other.vector_ + other.size_, vector_);
        }
        return *this;
    }

    reference operator[](size_t indx) {
        if (indx >= size_) {
            throw std::invalid_argument("invalid index");
        }
        return vector_[indx];
    }

    const_reference operator[](size_t indx) const {
        if (indx >= size_) {
            throw std::invalid_argument("invalid index");
        }
        return vector_[indx];
    }

    // getter
    size_t size() const { 
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    iterator begin() noexcept {
        return iterator(vector_);
    }

    iterator end() noexcept {
        return iterator(vector_ + size_);
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(vector_);
    }

    const_iterator cend() const noexcept {
        return const_iterator(vector_ + size_);
    }

    // methods
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T *temp = new T[new_capacity];
            std::copy(vector_, vector_ + size_, temp);
            delete[] vector_;
            vector_ = temp;
            capacity_ = new_capacity;
        }
    }

    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = size_; i < new_size; i++) {
            vector_[i] = T();
        }
        size_ = new_size;
    }


    void push_back(const T &value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        vector_[size_] = value;
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }
};

#endif // MYVECTOR_H