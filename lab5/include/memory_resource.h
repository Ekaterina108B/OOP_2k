#pragma once
#include <memory_resource>  
#include <map> 
#include <cstddef>
#include <algorithm>
#include <stdexcept>

class MemoryResource : public std::pmr::memory_resource {
private:
    char* pointer;
    size_t size;
    std::map<void*, size_t> allocated_blocks;
    std::map<size_t, std::pair<void*, size_t>> free_blocks; 

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit MemoryResource(size_t size); 
    ~MemoryResource();
    
    MemoryResource(const MemoryResource&) = delete;
    MemoryResource& operator=(const MemoryResource&) = delete;
}; 