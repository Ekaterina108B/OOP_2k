//Этот файл нужен для быстрого создания тестов от преподавателя

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

TEST_F(MemoryTest, additional_test){
    EXPECT_TRUE(true);
}