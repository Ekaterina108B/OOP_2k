#pragma once
#include <iterator> 
#include "pmr_node.h"

template<typename T>
class pmr_iterator {
private:
    using Node = pmr_node<T>;
    Node* current;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit pmr_iterator(Node* node) : current(node) {}
    
    pmr_iterator& operator++() {
        current = current->next;
        return *this;
    }
    
    pmr_iterator operator++(int) {
        pmr_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    
    reference operator*() { return current->data; }
    pointer operator->() { return &current->data; }
    
    bool operator==(const pmr_iterator& other) const {
        return current == other.current;
    }
    
    bool operator!=(const pmr_iterator& other) const {
        return !(current == other.current);
    }
}; 