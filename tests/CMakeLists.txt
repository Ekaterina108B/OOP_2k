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

add_executable(lab4_test lab4_tests.cpp ../lab4/include/figure.h ../lab4/include/rectangle.h ../lab4/include/trapezoid.h ../lab4/include/rhombus.h ../lab4/include/point.h ../lab4/include/array.h)

target_link_libraries(lab4_test PRIVATE GTest::GTest)
target_include_directories(lab4_test PRIVATE ../lab4/include)

add_test(lab4_test lab4_test)


add_executable(lab4_test+ lab4_tests+.cpp ../lab4/include/figure.h ../lab4/include/rectangle.h ../lab4/include/trapezoid.h ../lab4/include/rhombus.h ../lab4/include/point.h ../lab4/include/array.h)

target_link_libraries(lab4_test+ PRIVATE GTest::GTest)
target_include_directories(lab4_test+ PRIVATE ../lab4/include)

add_test(lab4_test+ lab4_test+)


