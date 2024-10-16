#include <gtest/gtest.h>
#include "brackets.h"

TEST(test_01, basic_test_set){
    std::string expression = "";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == true);
}

TEST(test_02, basic_test_set){
    std::string expression = "()";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == true);
}

TEST(test_03, basic_test_set){
    std::string expression = ")(()))";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == false);
}

TEST(test_04, basic_test_set){
    std::string expression = "(";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == false);
}

TEST(test_05, basic_test_set){
    std::string expression = "(())((()())())";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == true);
}

TEST(test_06, limit_of_symbol){
    std::string expression = "((((((((((((((((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))))))))";
    bool result = ValidateTheExpression(expression);
    ASSERT_TRUE(result == false);
}