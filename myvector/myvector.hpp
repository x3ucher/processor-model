#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>
#include <cstddef>
#include <memory>
#include <type_traits>

template<class T>
class MyVector;

/**
 * @class MVIterator
 * @brief Iterator class template for MyVector.
 * @tparam T The type of elements in the associated container.
 * @tparam is_const A boolean indicating whether the iterator is const or not.
 */
template<class T, bool is_const>
class MVIterator {
private:
    using ptr_t = std::conditional_t<is_const, const T, T>*; /**< Type for the iterator pointer. */
    ptr_t value; /**< Pointer to the current element. */

    /**
     * @brief Private constructor for MVIterator.
     * @param ptr Pointer to the current element.
     */
    MVIterator(ptr_t ptr) : value(ptr) {};

    friend MyVector<T>; /**< Friend declaration to allow access to MyVector. */
    friend MVIterator<T, !is_const>; /**< Friend declaration for the non-const version of the iterator. */
public:
    using difference_type = ptrdiff_t; /**< Type representing the difference between two iterators. */
    using value_type = T; /**< Type of elements in the associated container. */
    using pointer = std::conditional_t<is_const, const T*, T*>; /**< Type representing a pointer to the element type. */
    using reference = std::conditional_t<is_const, const T&, T&>; /**< Type representing a reference to the element type. */
    using iterator_category = std::bidirectional_iterator_tag; /**< Iterator category indicating bidirectional movement. */
    //===============================================================//

    /** Default constructor. */
    MVIterator() noexcept : value(nullptr) {}

    /**
     * @brief Copy constructor for MVIterator.
     * @param o The iterator to be copied.
     * @tparam other_const A boolean indicating whether the source iterator is const or not.
     * @note This constructor is enabled only if the source iterator is not more const than the destination iterator.
     */
    template<bool other_const>
    MVIterator(const MVIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) : value(o.value) {}
    
    //===============================================================//

    /**
     * @brief Copy assignment operator for MVIterator.
     * @param o The iterator to be copied.
     * @tparam other_const A boolean indicating whether the source iterator is const or not.
     * @return Reference to the assigned iterator.
     * @note This operator is enabled only if the source iterator is not more const than the destination iterator.
     */
    template<bool other_const>
    MVIterator& operator = (const MVIterator<T, other_const>& o) noexcept
        requires (is_const >= other_const) {
        value = o.value;
        return *this;
    }

    /**
     * @brief Dereference operator for MVIterator.
     * @return Reference to the element pointed by the iterator.
     */
    reference operator * () const noexcept {
        return *value;
    }

    /**
     * @brief Member access operator for MVIterator.
     * @return Pointer to the element pointed by the iterator.
     */
    pointer operator -> () const noexcept {
        return value;
    }

    /**
     * @brief Equality operator for MVIterator.
     * @param o The iterator to be compared.
     * @tparam other_const A boolean indicating whether the compared iterator is const or not.
     * @return True if the iterators are equal, false otherwise.
     */
    template<bool other_const>
    bool operator == (const MVIterator<T, other_const>& o) const noexcept {
        return value == o.value;
    }

    /**
     * @brief Inequality operator for MVIterator.
     * @param o The iterator to be compared.
     * @tparam other_const A boolean indicating whether the compared iterator is const or not.
     * @return True if the iterators are not equal, false otherwise.
     */
    template<bool other_const>
    bool operator != (const MVIterator<T, other_const>& o) const noexcept {
        return !(value != o.value);
    }

    /**
     * @brief Prefix increment operator for MVIterator.
     * @return Reference to the incremented iterator.
     */
    MVIterator& operator ++ () noexcept {
        ++value;
        return *this;
    }

    /**
     * @brief Postfix increment operator for MVIterator.
     * @param Dummy integer parameter (not used).
     * @return Copy of the iterator before incrementing.
     */
    MVIterator operator ++ (int) noexcept {
        MVIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    /**
     * @brief Prefix decrement operator for MVIterator.
     * @return Reference to the decremented iterator.
     */
    MVIterator& operator -- () noexcept {
        --value;
        return *this;
    }

    /**
     * @brief Postfix decrement operator for MVIterator.
     * @param Dummy integer parameter (not used).
     * @return Copy of the iterator before decrementing.
     */
    MVIterator operator -- (int) noexcept {
        MVIterator tmp = *this;
        --(*this);
        return *this;
    }
};

//===============================================================//


/**
 * @class MyVector
 * @brief Dynamic array implementation with basic vector operations.
 * @tparam T The type of elements in the vector.
 */
template<class T>
class MyVector {
private:
    T *vector_; /**< Pointer to the dynamic array. */
    size_t size_; /**< Number of elements in the vector. */
    size_t capacity_; /**< Capacity of the dynamic array. */

public:
    using iterator = MVIterator<T, false>; /**< Type alias for non-const iterator. */
    using const_iterator = MVIterator<T, true>; /**< Type alias for const iterator. */
    using value_type = T; /**< Type of elements in the vector. */
    using reference = T&; /**< Reference to elements in the vector. */
    using const_reference = const T&; /**< Const reference to elements in the vector. */
    using difference_type = ptrdiff_t; /**< Type representing the difference between two iterators. */
    using size_type = size_t; /**< Type representing the size of the vector. */
    //===============================================================//

    // constructor
    /** Default constructor. */
    MyVector() : vector_(nullptr), size_(0), capacity_(0) {}

    /**
     * @brief Constructor with a specified size.
     * @param size The initial size of the vector.
     */
    explicit MyVector(size_t size) : vector_(new T[size]), size_(size), capacity_(size) {}
    //===============================================================//

    // destructor
    /** Destructor. */
    ~MyVector() { 
        delete[] vector_;
        size_ = 0;
        capacity_ = 0;
    }
    //===============================================================//

    // copy constructor
    /**
     * @brief Copy constructor for MyVector.
     * @param other The vector to be copied.
     */
    MyVector(const MyVector<T> &other) : vector_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
        std::copy(other.vector_, other.vector_ + other.size_, vector_);
    }
    //===============================================================//
    
    // operators
    /**
     * @brief Copy assignment operator for MyVector.
     * @param other The vector to be assigned.
     * @return Reference to the assigned vector.
     */
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

    /**
     * @brief Access specified element with bounds checking.
     * @param indx The index of the element to be accessed.
     * @return Reference to the specified element.
     * @throws std::invalid_argument if the index is out of range.
     */
    reference operator[](size_t indx) {
        if (indx >= size_) {
            throw std::invalid_argument("invalid index");
        }
        return vector_[indx];
    }

    /**
     * @brief Access specified element with bounds checking (const version).
     * @param indx The index of the element to be accessed.
     * @return Const reference to the specified element.
     * @throws std::invalid_argument if the index is out of range.
     */
    const_reference operator[](size_t indx) const {
        if (indx >= size_) {
            throw std::invalid_argument("invalid index");
        }
        return vector_[indx];
    }
    //===============================================================//

    // getter
    /**
     * @brief Get the number of elements in the vector.
     * @return The number of elements in the vector.
     */
    size_t size() const { 
        return size_;
    }

    /**
     * @brief Get the capacity of the vector.
     * @return The capacity of the vector.
     */
    size_t capacity() const {
        return capacity_;
    }
    //===============================================================//

    /**
     * @brief Get the beginning iterator of the vector.
     * @return The beginning iterator.
     */
    iterator begin() noexcept {
        return iterator(vector_);
    }

    /**
     * @brief Get the ending iterator of the vector.
     * @return The ending iterator.
     */
    iterator end() noexcept {
        return iterator(vector_ + size_);
    }

    /**
     * @brief Get the beginning const iterator of the vector.
     * @return The beginning const iterator.
     */
    const_iterator cbegin() const noexcept {
        return const_iterator(vector_);
    }

    /**
     * @brief Get the ending const iterator of the vector.
     * @return The ending const iterator.
     */
    const_iterator cend() const noexcept {
        return const_iterator(vector_ + size_);
    }
    //===============================================================//

    // methods
    /**
     * @brief Reserve storage capacity for the vector.
     * @param new_capacity The new capacity to be reserved.
     */
    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T *temp = new T[new_capacity];
            std::copy(vector_, vector_ + size_, temp);
            delete[] vector_;
            vector_ = temp;
            capacity_ = new_capacity;
        }
    }

    /**
     * @brief Resize the vector to the specified size.
     * @param new_size The new size of the vector.
     */
    void resize(size_t new_size) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = size_; i < new_size; i++) {
            vector_[i] = T();
        }
        size_ = new_size;
    }

    /**
     * @brief Add an element to the end of the vector.
     * @param value The value of the element to be added.
     */
    void push_back(const T &value) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        vector_[size_] = value;
        size_++;
    }

    /**
     * @brief Remove the last element from the vector.
     */
    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }
};
//===============================================================//

#endif // MYVECTOR_H