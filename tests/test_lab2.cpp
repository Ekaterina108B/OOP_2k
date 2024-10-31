#include <gtest/gtest.h>
#include "seven.h"

TEST(addition_01, basic_test_set) {
    std::string result;
    Seven num1("123");
    Seven num2("456");
    
    Seven add = num1 + num2;
    result = add.toStr();

    ASSERT_TRUE(result == "612");
}

TEST(addition_02, basic_test_set) {
    std::string result;
    Seven num1("64");
    Seven num2("10");
    
    Seven add = num1 + num2;
    result = add.toStr();

    ASSERT_TRUE(result == "104");
}

TEST(addition_03, basic_test_set) {
    std::string result;
    Seven num1("121");
    Seven num2("66");
    
    Seven add = num1 + num2;
    result = add.toStr();

    ASSERT_TRUE(result == "220");
}

TEST(subtraction_01, basic_test_set) {
    std::string result;
    Seven num1("456");
    Seven num2("123");
    
    Seven add = num1 - num2;
    result = add.toStr();

    ASSERT_TRUE(result == "333");
}

TEST(subtraction_02, basic_test_set) {
    std::string result;
    Seven num1("12");
    Seven num2("123");
    
    Seven add = num1 - num2;
    result = add.toStr();

    ASSERT_TRUE(result == "0");
}

TEST(comparison_01, basic_test_set) {
    Seven num1("123");
    Seven num2("456");
    
    EXPECT_TRUE(num1 < num2);
}

TEST(comparison_02, basic_test_set) {
    Seven num1("123");
    Seven num2("456");
    
    EXPECT_FALSE(num1 > num2);
}

TEST(comparison_03, basic_test_set) {
    Seven num1("123");
    Seven num2("456");
    
    EXPECT_FALSE(num1 == num2);
}

TEST(comparison_04, basic_test_set) {
    Seven num1("456");
    Seven num2("456");
    
    EXPECT_TRUE(num1 == num2);
}

TEST(copying, basic_test_set) {
    std::string result;
    Seven num1("234");
    Seven num2 = num1;
    
    result = num2.toStr();

    EXPECT_TRUE(result == "234");
}

TEST(translation_01, basic_test_set) {
    std::string result;
    int num_10 = 0;
    Seven num(num_10);
    
    result = num.toStr();

    ASSERT_TRUE(result == "0");
}

TEST(translation_02, basic_test_set) {
    std::string result;
    int num_10 = 1;
    Seven num(num_10);
    
    result = num.toStr();

    ASSERT_TRUE(result == "1");
}

TEST(translation_03, basic_test_set) {
    std::string result;
    int num_10 = 7;
    Seven num(num_10);
    
    result = num.toStr();

    ASSERT_TRUE(result == "10");
}

TEST(translation_04, basic_test_set) {
    std::string result;
    int num_10 = 123;
    Seven num(num_10);
    
    result = num.toStr();

    ASSERT_TRUE(result == "234");
}