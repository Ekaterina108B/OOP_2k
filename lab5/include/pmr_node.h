#pragma once

template<typename T>
struct pmr_node {
    T data;
    pmr_node* next;
    
    pmr_node(const T& value) : data(value), next(nullptr) {}
}; 