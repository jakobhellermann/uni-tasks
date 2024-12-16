#ifndef SIMPLEARRAY_H
#define SIMPLEARRAY_H

#include <stdexcept>
#include <memory>
#include <cstring>

// Änderungen:
// m_array vom typ shared_ptr<T[]>
// kein Destruktor mehr

template<typename T>
class SimpleArray {
public:
    SimpleArray(size_t size);

    T &get(const size_t &index);

    const T &get(const size_t &index) const;

    void set(const size_t &index, T value);

    void resize(const size_t &newSize);

    size_t size() const;

private:
    std::shared_ptr<T[]> m_array;
    size_t m_size;
};

template<typename T>
SimpleArray<T>::SimpleArray(size_t size) {
    m_array = std::make_shared<T[]>(size);

    /*m_array = new T[size];
    if (m_array == nullptr) {
        throw std::bad_alloc();
    }*/
    m_size = size;
}

template<typename T>
T &SimpleArray<T>::get(const size_t &index) {
    if (index >= m_size) {
        throw std::runtime_error("index out of range");
    }
    return m_array[index];
}

template<typename T>
const T &SimpleArray<T>::get(const size_t &index) const {
    if (index >= m_size) {
        throw std::runtime_error("index out of range");
    }
    return m_array[index];
}

template<typename T>
void SimpleArray<T>::set(const size_t &index, T value) {
    if (index >= m_size) {
        throw std::runtime_error("index out of range");
    }
    m_array[index] = value;
}

template<typename T>
void SimpleArray<T>::resize(const size_t &newSize) {
    if (m_size == newSize) {
        return; // nothing to do
    }

    std::shared_ptr<T[]> newArray = std::make_shared<T[]>(newSize);
    memcpy(newArray.get(), m_array.get(), sizeof(T) * m_size);
    m_array = newArray;

    /*T *newArray = new T[newSize];
    memcpy(newArray, m_array, sizeof(T) * m_size);
    delete[] m_array;*/
    m_array = newArray;

    m_size = newSize;
}

template<typename T>
size_t SimpleArray<T>::size() const {
    return m_size;
}

#endif //SIMPLEARRAY_H
