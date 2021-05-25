#pragma once
#include <cmath>
#include <stdexcept>


template <class T>
class my_deque {
    size_t N, L, R;
    T* storage;
public:
    my_deque(const size_t &N = 1);
    size_t size() const;
    bool empty() const;
    void clear();
    T& front();
    T& back();
    void push_back(T new_el);
    void push_front(T new_el);
    void pop_front();
    void pop_back();
    const T& at(size_t pos) const;
    T& at(size_t pos);
    ~my_deque();
};


template <class T>
my_deque<T>::my_deque(const size_t &N) : N(N), L(0), R(N) {
    storage = new T[N];
}

template <class T>
size_t my_deque<T>::size() const {
    return R - L;
}

template <class T>
bool my_deque<T>::empty() const {
    return this->size() == 0;
}

template <class T>
void my_deque<T>::clear() {
    L = 0;
    R = 0;
}

template <class T>
T& my_deque<T>::front() {
    return *(storage + L);
}

template <class T>
T& my_deque<T>::back() {
    if (R == 0) {
        return *storage;
    } else {
        return *(storage + R);
    }
}

template <class T>
void my_deque<T>::push_back(T new_el) {
    if (R == N) {
        N *= 2;
        T* temp = new T[N];
        std::copy(storage, storage + R, temp);
        delete[] storage;
        storage = temp;
    }
    this->back() = new_el;
    R++;
}

template <class T>
void my_deque<T>::push_front(T new_el) {
    if (L == 0) {
        N *= 2;
        int* temp = new int[N];
        std::copy(storage, storage + R, temp + N/2);
        delete[] storage;
        storage = temp;
        R += N/2;
        L = N/2;
    }
    L--;
    this->front() = new_el;
}

template <class T>   
void my_deque<T>::pop_front() {
    L++;
}

template <class T>   
void my_deque<T>::pop_back() {
    R--;
}

template <class T>  
const T& my_deque<T>::at(size_t pos) const {
    if (pos < size()) {
        return *(storage + L + pos);
    } else {
        throw std::runtime_error("out of range");
    }
}

template <class T>  
T& my_deque<T>::at(size_t pos) {
    if (pos < size()) {
        return *(storage + L + pos);
    } else {
        throw std::runtime_error("out of range");
    }
}

template <class T> 
my_deque<T>::~my_deque() {
    delete[] storage;
}



