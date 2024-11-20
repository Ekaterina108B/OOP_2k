#include <gtest/gtest.h>
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include "array.h"
#include <sstream>

TEST(center, RectangleTest) {
    Rectangle<double> rectangle;
    std::stringstream ss("2 5 6 5 6 1 2 1");
    ss >> rectangle;
    
    auto center = rectangle.GetCenter();
    EXPECT_NEAR(center.GetX(), 4.0, 0.0001);
    EXPECT_NEAR(center.GetY(), 3.0, 0.0001);
}

TEST(area, RectangleTest) {
    Rectangle<double> rectangle;
    std::stringstream ss("-3 4 4 4 4 2 -3 2");
    ss >> rectangle;
    
    double area = static_cast<double>(rectangle);
    EXPECT_NEAR(area, 14.0, 0.0001);
}

TEST(equality, RectangleTest) {
    Rectangle<double> rectangle_1, rectangle_2;
    std::stringstream ss1("0 5 5 5 5 2 0 2");
    std::stringstream ss2("8 0 11 0 11 5 8 5");
    ss1 >> rectangle_1;
    ss2 >> rectangle_2;
    
    EXPECT_TRUE(rectangle_1 == rectangle_2);
}

//-----------------
TEST(center, TrapezoidTest) {
    Trapezoid<double> trapezoid;
    std::stringstream ss("10 10 11 12 12 10 11 8");
    ss >> trapezoid;
    
    auto center = trapezoid.GetCenter();
    EXPECT_NEAR(center.GetX(), 11.0, 0.0001);
    EXPECT_NEAR(center.GetY(), 10.0, 0.0001);
}

TEST(area, TrapezoidTest) {
    Trapezoid<double> trapezoid;
    std::stringstream ss("5 5 7 9 9 5 7 1");
    ss >> trapezoid;
    
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 16.0, 0.0001);
}

TEST(equality, TrapezoidTest) {
    Trapezoid<double> trapezoid_1, trapezoid_2;
    std::stringstream ss1("0 0 2 3 4 0 2 -3");
    std::stringstream ss2("1 1 3 4 5 1 3 -2");
    ss1 >> trapezoid_1;
    ss2 >> trapezoid_2;
    
    EXPECT_TRUE(trapezoid_1 == trapezoid_2);
}

//-----------------
TEST(center, RhombusTest) {
    Rhombus<double> rhombus;
    std::stringstream ss("6 0 9 -2 12 0 9 2");
    ss >> rhombus;
    
    auto center = rhombus.GetCenter();
    EXPECT_NEAR(center.GetX(), 9.0, 0.0001);
    EXPECT_NEAR(center.GetY(), 0.0, 0.0001);
}

TEST(area, RhombusTest) {
    Rhombus<double> rhombus;
    std::stringstream ss("6 0 9 -2 12 0 9 2");
    ss >> rhombus;
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 12.0, 0.0001);
}

TEST(equality, RhombusTest) {
    Rhombus<double> rhombus_1, rhombus_2;
    std::stringstream ss1("6 0 9 -2 12 0 9 2");
    std::stringstream ss2("0 0 2 -3 4 0 2 3");
    ss1 >> rhombus_1;
    ss2 >> rhombus_2;
    
    EXPECT_TRUE(rhombus_1 == rhombus_2);
}

//-----------------
TEST(copy, OperationsTest) {
    Rectangle<double> rectangle_1;
    Rectangle<double> rectangle_2;

    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle_1;
    rectangle_2 = rectangle_1;
    EXPECT_TRUE(rectangle_1 == rectangle_2);
}

TEST(move, OperationsTest) {
    Rectangle<double> rectangle_1;
    Rectangle<double> rectangle_2;
    Rectangle<double> expected;
    
    std::stringstream ss("0 0 4 0 4 3 0 3");
    std::stringstream ss2("0 0 4 0 4 3 0 3");
    ss2 >> expected;
    ss >> rectangle_1;
    rectangle_2 = std::move(rectangle_1);
    
    EXPECT_TRUE(rectangle_2 == expected);
}