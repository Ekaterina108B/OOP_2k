#include "memory_resource.h"

MemoryResource::MemoryResource(size_t size) : size(size) {
    pointer = new char[size];
    free_blocks[0] = std::make_pair(pointer, size);
}

MemoryResource::~MemoryResource() {
    delete[] pointer;
}

void* MemoryResource::do_allocate(size_t bytes, size_t alignment) {
    for (auto i = free_blocks.begin(); i != free_blocks.end(); ++i) {
        void* ptr = i->second.first;
        size_t size_i = i->second.second;
        
        std::uintptr_t raw_addr = reinterpret_cast<std::uintptr_t>(ptr);
        std::uintptr_t aligned_addr = (raw_addr + alignment - 1) & ~(alignment - 1);
        size_t adjustment = aligned_addr - raw_addr;
        
        if (size_i >= bytes + adjustment) {
            free_blocks.erase(i);
            
            if (adjustment > 0) {
                free_blocks[reinterpret_cast<size_t>(ptr)] = 
                    std::make_pair(ptr, adjustment);
                ptr = reinterpret_cast<void*>(aligned_addr);
                size_i -= adjustment;
            }
            
            allocated_blocks[ptr] = bytes;
            
            if (size_i > bytes) {
                void* remaining = static_cast<char*>(ptr) + bytes;
                free_blocks[reinterpret_cast<size_t>(remaining)] = 
                    std::make_pair(remaining, size_i - bytes);
            }
            
            return ptr;
        }
    }
    throw std::bad_alloc();
}

void MemoryResource::do_deallocate(void* p, size_t bytes, size_t) {
    auto i = allocated_blocks.find(p);
    if (i != allocated_blocks.end()) {
        free_blocks[reinterpret_cast<size_t>(p)] = std::make_pair(p, bytes);
        allocated_blocks.erase(i);
        
        auto current = free_blocks.find(reinterpret_cast<size_t>(p));
        
        auto next = std::next(current);
        if (next != free_blocks.end() && 
            static_cast<char*>(current->second.first) + current->second.second == 
            static_cast<char*>(next->second.first)) {
            current->second.second += next->second.second;
            free_blocks.erase(next);
        }
        
        if (current != free_blocks.begin()) {
            auto prev = std::prev(current);
            if (static_cast<char*>(prev->second.first) + prev->second.second == 
                static_cast<char*>(current->second.first)) {
                prev->second.second += current->second.second;
                free_blocks.erase(current);
            }
        }
    }
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}