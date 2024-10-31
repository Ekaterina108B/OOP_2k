//Этот файл нужен для быстрого создания тестов от преподавателя

#include <gtest/gtest.h>
#include "brackets.h"

TEST(test_01, additional_test){
    std::string expression = "";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == true);
}