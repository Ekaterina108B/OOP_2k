#include <gtest/gtest.h>
#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"
#include <sstream>

// Тесты для Rectangle
TEST(RectangleTest, CenterCalculation) {
    Rectangle rectangle;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle;
    
    auto center = rectangle.GetCenter();
    EXPECT_NEAR(center.x, 2.0, 0.0001);
    EXPECT_NEAR(center.y, 1.5, 0.0001);
}

TEST(RectangleTest, AreaCalculation) {
    Rectangle rectangle;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> rectangle;
    
    double area = static_cast<double>(rectangle);
    EXPECT_NEAR(area, 12.0, 0.0001);
}

TEST(RectangleTest, Equality) {
    Rectangle r1, r2;
    std::stringstream ss1("0 0 4 0 4 3 0 3");
    std::stringstream ss2("0 0 4 0 4 3 0 3");
    ss1 >> r1;
    ss2 >> r2;
    
    EXPECT_TRUE(r1 == r2);
}

// Тесты для Trapezoid
TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid trapezoid;
    std::stringstream ss("0 0 6 0 4 3 2 3");
    ss >> trapezoid;
    
    auto center = trapezoid.GetCenter();
    EXPECT_NEAR(center.x, 3.0, 0.0001);
    EXPECT_NEAR(center.y, 1.5, 0.0001);
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid trapezoid;
    std::stringstream ss("0 0 6 0 4 3 2 3");
    ss >> trapezoid;
    
    double area = static_cast<double>(trapezoid);
    EXPECT_NEAR(area, 12.0, 0.0001);
}

TEST(TrapezoidTest, Equality) {
    Trapezoid t1, t2;
    std::stringstream ss1("0 0 6 0 4 3 2 3");
    std::stringstream ss2("0 0 6 0 4 3 2 3");
    ss1 >> t1;
    ss2 >> t2;
    
    EXPECT_TRUE(t1 == t2);
}

// Тесты для Rhombus
TEST(RhombusTest, CenterCalculation) {
    Rhombus rhombus;
    std::stringstream ss("0 2 2 4 4 2 2 0");
    ss >> rhombus;
    
    auto center = rhombus.GetCenter();
    EXPECT_NEAR(center.x, 2.0, 0.0001);
    EXPECT_NEAR(center.y, 2.0, 0.0001);
}

TEST(RhombusTest, AreaCalculation) {
    Rhombus rhombus;
    std::stringstream ss("0 2 2 4 4 2 2 0");
    ss >> rhombus;
    
    double area = static_cast<double>(rhombus);
    EXPECT_NEAR(area, 8.0, 0.0001);
}

TEST(RhombusTest, Equality) {
    Rhombus r1, r2;
    std::stringstream ss1("0 2 2 4 4 2 2 0");
    std::stringstream ss2("0 2 2 4 4 2 2 0");
    ss1 >> r1;
    ss2 >> r2;
    
    EXPECT_TRUE(r1 == r2);
}

// Тесты для операций копирования и перемещения
TEST(OperationsTest, CopyAssignment) {
    Rectangle r1;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> r1;
    
    Rectangle r2;
    r2 = r1;
    EXPECT_TRUE(r1 == r2);
}

TEST(OperationsTest, MoveAssignment) {
    Rectangle r1;
    std::stringstream ss("0 0 4 0 4 3 0 3");
    ss >> r1;
    
    Rectangle r2;
    r2 = std::move(r1);
    
    Rectangle expected;
    std::stringstream ss2("0 0 4 0 4 3 0 3");
    ss2 >> expected;
    EXPECT_TRUE(r2 == expected);
}