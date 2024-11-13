#include <gtest/gtest.h>
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include <sstream>

//-----------------
TEST(center, RectangleTest) {
    Rectangle rectangle;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle;
    
    auto center = rectangle.GetCenter();
    EXPECT_NEAR(center.x, 2.0, 0.0001);
    EXPECT_NEAR(center.y, 1.5, 0.0001);
}

TEST(area, RectangleTest) {
    Rectangle rectangle;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle;
    
    double area = static_cast<double>(rectangle);
    EXPECT_NEAR(area, 12.0, 0.0001);
}

TEST(equality, RectangleTest) {
    Rectangle rectangle_1, rectangle_2;
    std::stringstream ss1("0 0 5 0 5 3 0 3");
    std::stringstream ss2("8 0 11 0 11 5 8 5");
    ss1 >> rectangle_1;
    ss2 >> rectangle_2;
    
    EXPECT_TRUE(rectangle_1 == rectangle_2);
}

//-----------------
TEST(center, TrapezoidTest) {
    Trapezoid trapezoid;
    std::stringstream ss("0 0 6 0 4 3 2 3");
    ss >> trapezoid;
    
    auto center = trapezoid.GetCenter();
    EXPECT_NEAR(center.x, 3.0, 0.0001);
    EXPECT_NEAR(center.y, 1.5, 0.0001);
}

TEST(area, TrapezoidTest) {
    Trapezoid trapezoid;
    std::stringstream ss("0 0 6 0 4 3 2 3");
    ss >> trapezoid;
    
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 12.0, 0.0001);
}

TEST(equality, TrapezoidTest) {
    Trapezoid trapezoid_1, trapezoid_2;
    std::stringstream ss1("0 0 5 0 5 3 3 3");
    std::stringstream ss2("8 0 13 0 10 3 8 3");
    ss1 >> trapezoid_1;
    ss2 >> trapezoid_2;
    
    EXPECT_TRUE(trapezoid_1 == trapezoid_2);
}

//-----------------
TEST(center, RhombusTest) {
    Rhombus rhombus;
    std::stringstream ss("0 2 2 4 4 2 2 0");
    ss >> rhombus;
    
    auto center = rhombus.GetCenter();
    EXPECT_NEAR(center.x, 2.0, 0.0001);
    EXPECT_NEAR(center.y, 2.0, 0.0001);
}

TEST(area, RhombusTest) {
    Rhombus rhombus;
    std::stringstream ss("0 2 2 4 4 2 2 0");
    ss >> rhombus;
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 8.0, 0.0001);
}

TEST(equality, RhombusTest) {
    Rhombus rhombus_1, rhombus_2;
    std::stringstream ss1("0 0 2 -3 4 0 2 3");
    std::stringstream ss2("6 0 9 -2 12 0 9 2");
    ss1 >> rhombus_1;
    ss2 >> rhombus_2;
    
    EXPECT_TRUE(rhombus_1 == rhombus_2);
}

//-----------------
TEST(copy, OperationsTest) {
    Rectangle rectangle_1;
    Rectangle rectangle_2;

    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle_1;
    rectangle_2 = rectangle_1;
    EXPECT_TRUE(rectangle_1 == rectangle_2);
}

TEST(move, OperationsTest) {
    Rectangle rectangle_1;
    Rectangle rectangle_2;
    Rectangle expected;
    
    std::stringstream ss("0 0 4 0 4 3 0 3");
    std::stringstream ss2("0 0 4 0 4 3 0 3");
    ss2 >> expected;
    ss >> rectangle_1;
    rectangle_2 = std::move(rectangle_1);
    
    EXPECT_TRUE(rectangle_2 == expected);
}