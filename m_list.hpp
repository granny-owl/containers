#pragma once
#include <algorithm>

template<class T>
class list {   
    struct node {
        T value;
        node* next;
    };

    node* m_begin;
    node* m_end;
    node* pre_end;
    size_t m_size;
public:    
    class m_iterator {
        friend class list;
        node* its_node;
        m_iterator(node* p = nullptr);

    public:
        m_iterator(const m_iterator& iter);
        m_iterator(m_iterator&& iter);
        m_iterator& operator++ ();
        m_iterator operator++ (int);
        m_iterator operator+ (size_t add);
        bool operator== (m_iterator it) const;
        bool operator!= (m_iterator it) const;
        T& operator* ();
        const T& operator* () const;
        m_iterator& operator= (m_iterator bar);  
    };

    list();
    m_iterator emplace_back (T n_val);
    m_iterator emplace_after(m_iterator pos, T n_val);
    m_iterator begin() const;
    m_iterator end() const;
    size_t size() const;
    void clear();
    m_iterator erase (m_iterator pos);
    ~list();
};


template <class T>
list<T>::m_iterator::m_iterator(node* p) {
    this->its_node = p;
}

template <class T>
list<T>::m_iterator::m_iterator(const m_iterator& iter) {
    this->its_node = iter.its_node;
}

template <class T>
list<T>::m_iterator::m_iterator(m_iterator&& iter) {
    this->its_node = std::move(iter.its_node);
    iter.its_node = nullptr;
}

template <class T>
typename list<T>::m_iterator& list<T>::m_iterator::operator++ () {
    this->its_node = this->its_node->next;
    return *this;
}

template <class T>
typename list<T>::m_iterator list<T>::m_iterator::operator++ (int) {
    m_iterator it = *this;
    ++(*this);
    return it;
}

template <class T>
typename list<T>::m_iterator list<T>::m_iterator::operator+ (size_t add) {
    m_iterator foo = *this;
    while (add > 0) {
        foo.its_node = foo.its_node->next;
        add--;
    }
    return foo;
}

template <class T>
bool list<T>::m_iterator::operator== (m_iterator it) const {
    return this->its_node == it.its_node; 
}

template <class T>
bool list<T>::m_iterator::operator!= (m_iterator it) const {
    return this->its_node != it.its_node; 
}

template <class T>
T& list<T>::m_iterator::operator* () {
    return this->its_node->value;
}

template <class T>
const T& list<T>::m_iterator::operator* () const {
    return this->its_node->value;
}

template <class T>
typename list<T>::m_iterator& list<T>::m_iterator::operator= (m_iterator bar) {
    this->its_node = bar.its_node;
    return *this;
}

template <class T>
list<T>::list() {
    m_size = 0;
    node* temp = new node();
    m_end = temp;
    m_begin = temp;    
}

template <class T>
typename list<T>::m_iterator list<T>::emplace_back (T n_val) {
    node* new_node = new node();
    new_node->value = n_val;
    if (size() == 0) {
        m_begin = new_node;
    } else {
        pre_end->next = new_node;
    }
    pre_end = new_node;
    new_node->next = m_end;
    m_size++;
    return {new_node};
}

template <class T>
typename list<T>::m_iterator list<T>::emplace_after (m_iterator pos, T n_val) {
    node* new_node = new node();
    new_node->value = n_val;
    if (size() == 0) {
        m_begin = new_node;
        pre_end = new_node;
        new_node->next = m_end;
    } else {
        if (pos.its_node->next == m_end) {
            pos.its_node->next = new_node;
            new_node->next = m_end;
            pre_end = new_node;
        } else {
            new_node->next = pos.its_node->next;
            pos.its_node->next = new_node;
        }        
    }
    m_size++;
    return {new_node};
}

template <class T>
typename list<T>::m_iterator list<T>::begin() const {
    return {m_begin};
}

template <class T>
typename list<T>::m_iterator list<T>::end() const {
    return {m_end};
}

template <class T>
size_t list<T>::size() const {
    return m_size;   
}

template <class T>
void list<T>::clear() {
    for (auto it = this->begin(); it != this->end(); ) {
        m_iterator foo = it+1;
        delete it.its_node;
        it = foo;
    }
    delete m_end;
    m_size = 0;
    node* temp = new node();
    m_end = temp;
    m_begin = temp;      
}

template <class T>
typename list<T>::m_iterator list<T>::erase (m_iterator pos) {
    node* left;
    if (m_size == 1) {
        clear();
    }

    if (m_size > 1) {
        if (pos.its_node == m_begin) {
            m_begin = pos.its_node->next;
        } else {
            left = m_begin;
            while (left->next != pos.its_node) {
                left = left->next;
            }
            left->next = pos.its_node->next;
        }
        delete pos.its_node;
        m_size--;
    }

    m_iterator ret_it;
    if (m_size == 0) {
        ret_it = m_iterator(m_begin);
    } else {
        ret_it = m_iterator(left->next);
    }
    return ret_it; 
}

template <class T>
list<T>::~list() {
    for (auto it = this->begin(); it != this->end(); ) {
        auto foo = it+1;
        delete it.its_node;
        it = foo;
    }
    delete m_end;
} 
