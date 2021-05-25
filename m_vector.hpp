#pragma once
#include <algorithm>


template <class T>
class m_vector {
    size_t m_cap;
    T* storage;
    T* last;
    T* after_last;
    void widen_storage(); //doubles storage; only for use inside the class

public:
    m_vector(size_t new_size = 0);

    class m_it {                               //iterator
        friend struct m_vector;
        T* its_pos;
        m_it(T* p = nullptr);

    public:
        m_it(const m_it & iter);               //copy constructor
        m_it(m_it&& it);                       //move constructor
        m_it operator+ (const size_t & add);
        m_it operator++ (int);
        m_it operator-- (int);
        bool operator== (m_it it) const;
        bool operator!= (m_it it) const;
        m_it& operator= (m_it it);
        T& operator* ();
        const T& operator* () const;
    };

    m_vector<T> (const m_vector<T>& orig);   //copy constructor
    T& at (size_t pos);                      //at()
    m_it begin() const;                      //begin()
    m_it end() const;                        //end()
    size_t size() const;                     //size()
    void clear();                            //clear()
    m_it erase(m_it elem);                   //erase()
    m_it insert(m_it it, T n_val);           //insert()
    void push_back(T n_val);                 //push_back()
    bool empty() const;                      //empty()
    void shrink();                           //shrink()
    ~m_vector();                             //destructor
}; 


template <class T>
void m_vector<T>::widen_storage() {
    if (after_last == storage + m_cap) {
        m_cap *= 2;
        T* temp = new T[m_cap];
        size_t temp_al = after_last - storage;
        size_t temp_l = last - storage;
        std::copy(storage, after_last, temp);
        delete[] storage;
        storage = temp;   
        after_last = storage + temp_al;
        last = storage + temp_l;
    }  
}

template <class T>
m_vector<T>::m_vector(size_t new_size) {
    new_size == 0 ? m_cap = 1 : m_cap = new_size;
    storage = new T[m_cap];
    if (new_size == 0) {
        after_last = storage;
        last = storage;  
    } else {
        after_last = storage + m_cap;
        last = storage + m_cap - 1;  
    }
}

template <class T>
m_vector<T>::m_it::m_it(T* p) : its_pos(p) {}

template <class T>
m_vector<T>::m_it::m_it(const m_it& iter) : its_pos(iter.its_pos) {}

template <class T>
m_vector<T>::m_it::m_it(m_it&& it) {
    its_pos = std::move(it.its_pos);
    it.its_pos = nullptr;   
}

template <class T>
typename m_vector<T>::m_it m_vector<T>::m_it::operator+ (const size_t & add) {
    m_it foo = *this;
    foo.its_pos += add; 
    return foo;
}

template <class T>
typename m_vector<T>::m_it m_vector<T>::m_it::operator++ (int) {
    *this->its_pos++;
    return *this;
}

template <class T>
typename m_vector<T>::m_it m_vector<T>::m_it::operator-- (int) {
    *this->its_pos--;
    return *this;
}

template <class T>
bool m_vector<T>::m_it::operator== (m_it it) const {
    return its_pos == it.its_pos;
}

template <class T>
bool m_vector<T>::m_it::operator!= (m_it it) const {
    return its_pos != it.its_pos;
}

template <class T>
typename m_vector<T>::m_it& m_vector<T>::m_it::operator= (m_it it) {
    its_pos = it.its_pos;
    return *this;
}

template <class T>
T& m_vector<T>::m_it::operator* () {
    return *(this->its_pos);
} 

template <class T>
m_vector<T>::m_vector(const m_vector<T>& orig) {
    m_cap = orig.m_cap;
    storage = new T[m_cap];
    last = storage + (orig.last - orig.storage);
    after_last = storage + (orig.after_last - orig.storage);
    std::copy(orig.storage, orig.after_last, storage);
}

template <class T>
T& m_vector<T>::at(size_t pos) {
    return *(storage + pos);
} 

template <class T>
typename m_vector<T>::m_it m_vector<T>::begin() const {
    return m_it(storage);
}

template <class T>
typename m_vector<T>::m_it m_vector<T>::end() const {
    return m_it(after_last);
}

template <class T>
size_t m_vector<T>::size() const {
    size_t val;
    if (after_last == storage) {
        val = 0;
    } else {
        val = after_last - storage;
    }  
    return val;     
}

template <class T>
void m_vector<T>::clear() {
    m_vector* n_vec = new m_vector();
    this->~m_vector();
    *this = *n_vec;
} 

template <class T>
typename m_vector<T>::m_it m_vector<T>::erase(m_it elem) {
    m_it return_it;
    if (size() < 2) {
        clear();
        return_it = m_it(after_last);
    } else {
        m_it pre_end = m_it(last); 
        for (auto it = elem; it != pre_end; it++) {
            *(it) = *(it+1);
        }
        last--;
        after_last--;
        return_it = elem;
    }
    return return_it; 
} 

template <class T>
typename m_vector<T>::m_it m_vector<T>::insert (m_it it, T n_val) {
    widen_storage();
    size_t temp_add = it.its_pos - storage;
    it.its_pos = storage + temp_add;
    std::copy(it.its_pos, after_last, it.its_pos + 1);
    *it.its_pos = n_val;
    if (size() > 0) last++;             
    after_last++;
    return it;        
}

template <class T>
void m_vector<T>::push_back(T n_val) {
    widen_storage();
    *after_last = n_val;
    if (size() > 0) last++;             
    after_last++;  
}

template <class T>
bool m_vector<T>::empty() const {
    return size() == 0;
} 

template <class T>
void m_vector<T>::shrink() {
    size_t temp_al = after_last - storage;
    size_t temp_l = last - storage;
    T* temp = new T[temp_al];
    std::copy(storage, after_last, temp);
    delete[] storage;
    storage = temp;   
    after_last = storage + temp_al;
    last = storage + temp_l;   
    if (after_last == storage) {
        this->m_cap = 1;
    } else {
        this->m_cap = after_last - storage;
    }   
}

template <class T>
m_vector<T>::~m_vector() {
    delete[] storage;
} 
