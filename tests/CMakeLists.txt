include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

add_executable(lab3_test lab3_test.cpp ../lab3/include/figure.h ../lab3/include/rectangle.h ../lab3/include/trapezoid.h ../lab3/include/rhombus.h ../lab3/src/rectangle.cpp ../lab3/src/trapezoid.cpp ../lab3/src/rhombus.cpp ../lab3/include/array.h ../lab3/src/array.cpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)


add_executable(lab3_test+ lab3_test+.cpp ../lab3/include/figure.h ../lab3/include/rectangle.h ../lab3/include/trapezoid.h ../lab3/include/rhombus.h ../lab3/src/rectangle.cpp ../lab3/src/trapezoid.cpp ../lab3/src/rhombus.cpp ../lab3/include/array.h ../lab3/src/array.cpp)

target_link_libraries(lab3_test+ PRIVATE GTest::GTest)
target_include_directories(lab3_test+ PRIVATE ../lab1/include)

add_test(lab3_test+ lab3_test+)

