#pragma once
#include <cmath>
#include <stdexcept>


template <class T>
class m_array {
    int N;
    T* storage;
public:
    m_array(int N);
    int size();
    T& at(int pos);
    const T& m_at(int pos) const;
    ~m_array();
};


template <class T>
m_array<T>::m_array(int N) {
    this->N = N;
    storage = new T[N];
}

template <class T>
int m_array<T>::m_size() {
    return N;
} 

template <class T>
T& m_array<T>::at(int pos) {
    if (pos > -1 && pos < N) {
        return *(storage + pos);
    } else {
        throw std::runtime_error("out of range");
    }
} 

template <class T>
const T& m_array<T>::at(int pos) const {
    if (pos > -1 && pos < N) {
        return *(storage + pos);
    } else {
        throw std::runtime_error("out of range");
    }
}

template <class T>
m_array<T>::~m_array() {
    delete[] storage;
}   



        
