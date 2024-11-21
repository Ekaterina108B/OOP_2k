#pragma once
#include <memory_resource>
#include "pmr_node.h"
#include "pmr_iterator.h"

template<typename T>
class pmr_list {
private:
    using Node = pmr_node<T>;
    Node* head;
    std::pmr::polymorphic_allocator<Node> allocator;

public:
    using iterator = pmr_iterator<T>;

    explicit pmr_list(std::pmr::memory_resource* resource = nullptr) : head(nullptr), allocator(resource) {}
    
    ~pmr_list() { clear(); }

    void PushFront(const T& value) {
        Node* new_node = allocator.allocate(1);
        allocator.construct(new_node, value);
        new_node->next = head;
        head = new_node;
    }
    void PopFront() {
        if(head) {
            Node* old_head = head;
            head = head->next;
            allocator.destroy(old_head);
            allocator.deallocate(old_head, 1);
        }
    }
    
    void PushBack(const T& value) {
        Node* new_node = allocator.allocate(1);
        allocator.construct(new_node, value);
        new_node->next = nullptr;
        if(!head) {
            head = new_node;
        } else {
            Node* current = head;
            while(current->next) { current = current->next; }
            current->next = new_node;
        }
    }
    void PopBack() {
        if(!head) { return; }
        if(!head->next) {
            allocator.destroy(head);
            allocator.deallocate(head, 1);
            head = nullptr;
            return;
        }
        Node* current = head;
        while(current->next->next) { current = current->next; }
        allocator.destroy(current->next);
        allocator.deallocate(current->next, 1);
        current->next = nullptr;
    }

    void InsertAfter(const T& node, const T& value) {
        Node* current = head;
        while(current || current->data != node) { current = current->next; }
        if(current == nullptr) { return; }
        Node* new_node = allocator.allocate(1);
        allocator.construct(new_node, value);
        new_node->next = current->next;
        current->next = new_node;
    }
    void EraseAfter(const T& node) {
        Node* current = head;
        while(current || current->data != node) { current = current->next; }
        if(!current || !current->next){ return; }
        Node* old_node = current->next;
        current->next = old_node->next;
        allocator.destroy(old_node);
        allocator.deallocate(old_node, 1);
    }
    
    void clear() {
        while(head) {
            PopFront();
        }
    }
    
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
}; 