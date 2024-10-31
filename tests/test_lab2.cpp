#include <gtest/gtest.h>
#include "seven.h"

TEST(SevenTest, Addition) {
    Seven num1, num2, result;
    
    num1.fromString("123");
    num2.fromString("456");
    
    result = num1 + num2; // Предполагаем, что оператор + перегружен

    EXPECT_EQ(result.toString(), "1023"); // Ожидаем результат сложения
}

// Тест для проверки вычитания
TEST(SevenTest, Subtraction) {
    Seven num1, num2, result;
    
    num1.fromString("456");
    num2.fromString("123");
    
    result = num1 - num2; // Предполагаем, что оператор - перегружен

    EXPECT_EQ(result.toString(), "333"); // Ожидаем результат вычитания
}

// Тест для проверки операций сравнения
TEST(SevenTest, Comparison) {
    Seven num1, num2;
    
    num1.fromString("123");
    num2.fromString("456");
    
    EXPECT_TRUE(num1 < num2); // Ожидаем, что num1 меньше num2
    EXPECT_FALSE(num1 > num2); // num1 не больше num2
    EXPECT_FALSE(num1 == num2); // num1 не равно num2
    
    num1.fromString("456");
    EXPECT_TRUE(num1 == num2); // num1 теперь равно num2
}

// Тест для проверки копирования
TEST(SevenTest, Copying) {
    Seven num1;
    num1.fromString("234");
    Seven num2 = num1; // Используем оператор присваивания
    
    EXPECT_EQ(num2.toString(), "234"); // Ожидаем, что num2 равен num1
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}