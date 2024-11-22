#include <gtest/gtest.h>
#include "pmr_list.h"
#include "memory_resource.h"
#include "complextype.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class MemoryTest : public ::testing::Test {
protected:
    static constexpr size_t DEFAULT_MEMORY_SIZE = 1024 * 1024; // 1MB
    std::unique_ptr<MemoryResource> resource;

    void SetUp() override {
        resource = std::make_unique<MemoryResource>(DEFAULT_MEMORY_SIZE);
    }
};

TEST_F(MemoryTest, basic_allocation) {
    void* ptr_1 = resource->allocate(100);
    ASSERT_NE(ptr_1, nullptr);
    
    void* ptr_2 = resource->allocate(200);
    ASSERT_NE(ptr_2, nullptr);
    ASSERT_NE(ptr_1, ptr_2);

    resource->deallocate(ptr_1, 100);
    resource->deallocate(ptr_2, 200);
}

TEST_F(MemoryTest, memory_reuse) {
    void* ptr_1 = resource->allocate(100);
    void* original_ptr = ptr_1;
    
    resource->deallocate(ptr_1, 100);
    void* ptr_2 = resource->allocate(100);
    EXPECT_EQ(ptr_2, original_ptr);
}

TEST_F(MemoryTest, fragmentation_handling) {
    std::vector<void*> ptrs;
    
    for(int i = 0; i < 5; i++) {
        ptrs.push_back(resource->allocate(100));
    }
    
    for(size_t i = 0; i < ptrs.size(); i += 2) {
        resource->deallocate(ptrs[i], 100);
    }
    
    void* large_ptr = resource->allocate(250);
    ASSERT_NE(large_ptr, nullptr);
}

TEST_F(MemoryTest, out_of_memory) {
    MemoryResource small_resource(100);
    
    void* ptr_1 = small_resource.allocate(50);
    ASSERT_NE(ptr_1, nullptr);
    
    try {
        [[maybe_unused]] void* ptr_2 = small_resource.allocate(60);
        FAIL() << "Expected std::bad_alloc";
    } catch (const std::bad_alloc&) {
    }
}

TEST_F(MemoryTest, alignment_test) {
    void* ptr_1 = resource->allocate(10, 8);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_1) % 8, 0);
    
    void* ptr_2 = resource->allocate(10, 16);
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr_2) % 16, 0);
    
    resource->deallocate(ptr_1, 10, 8);
    resource->deallocate(ptr_2, 10, 16);
}

TEST_F(MemoryTest, coalescing_test) {
    void* ptr_1 = resource->allocate(100);
    void* ptr_2 = resource->allocate(100);
    void* ptr3 = resource->allocate(100);
    
    resource->deallocate(ptr3, 100);
    resource->deallocate(ptr_2, 100);
    resource->deallocate(ptr_1, 100);
    
    void* large_ptr = resource->allocate(250);
    ASSERT_NE(large_ptr, nullptr);
    EXPECT_EQ(large_ptr, ptr_1);
}

TEST_F(MemoryTest, integer_operations) {
    pmr_list<int> list(resource.get());
    
    list.PushFront(1);
    list.PushBack(2);
    list.InsertAfter(1, 3);
    
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(it, list.end());
    
    list.PopFront();
    EXPECT_EQ(*list.begin(), 3);
}

TEST_F(MemoryTest, complextype_operations) {
    pmr_list<ComplexType> complex_list(resource.get());
    
    ComplexType objectect_1;
    objectect_1.id = 1;
    objectect_1.value = 1.1;
    objectect_1.name = "one";
    objectect_1.data = {1, 2, 3};
    objectect_1.active = true;

    ComplexType objectect_2;
    objectect_2.id = 2;
    objectect_2.value = 2.2;
    objectect_2.name = "two";
    objectect_2.data = {4, 5, 6};
    objectect_2.active = false;
    
    ComplexType objectect_3;
    objectect_3.id = 3;
    objectect_3.value = 3.3;
    objectect_3.name = "tri";
    objectect_3.data = {7, 8, 9};
    objectect_3.active = false;
    complex_list.PushFront(objectect_1);
    complex_list.PushBack(objectect_2);
    complex_list.InsertAfter(objectect_1, objectect_3);
    
    auto it = complex_list.begin();
    EXPECT_EQ(it->id, 1);
    EXPECT_DOUBLE_EQ(it->value, 1.1);
    EXPECT_EQ(it->name, "one");
    EXPECT_EQ(it->data, std::vector<int>({1, 2, 3}));
    EXPECT_TRUE(it->active);
    
    ++it;
    EXPECT_EQ(it->id, 3);
    EXPECT_DOUBLE_EQ(it->value, 3.3);
    EXPECT_EQ(it->name, "tri");
    EXPECT_EQ(it->data, std::vector<int>({7, 8, 9}));
    EXPECT_FALSE(it->active);

    ++it;
    EXPECT_EQ(it->id, 2);
    EXPECT_DOUBLE_EQ(it->value, 2.2);
    EXPECT_EQ(it->name, "two");
    EXPECT_EQ(it->data, std::vector<int>({4, 5, 6}));
    EXPECT_FALSE(it->active);
}

TEST_F(MemoryTest, empty_list_operations) {
    pmr_list<int> list(resource.get());
    
    EXPECT_EQ(list.begin(), list.end());
    list.PopFront();
    list.Clear();
}

TEST_F(MemoryTest, iterator_operations) {
    pmr_list<int> list(resource.get());
    list.PushFront(1);
    list.PushFront(2);
    
    auto it = list.begin();
    
    auto old_it = it++;
    EXPECT_EQ(*old_it, 2);
    EXPECT_EQ(*it, 1);
    
    it = list.begin();
    auto& ref = ++it;
    EXPECT_EQ(&ref, &it);
    EXPECT_EQ(*it, 1);
}

TEST_F(MemoryTest, list_memory_reuse) {
    pmr_list<int> list(resource.get());
    
    for (int i = 0; i < 5; ++i) {
        list.PushFront(i);
        list.PushFront(i + 1);
        list.Clear();
    }
    
    list.PushFront(42);
    EXPECT_EQ(*list.begin(), 42);
}