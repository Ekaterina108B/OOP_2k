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

add_executable(lab1_test lab1_tests.cpp ../lab1/src/brackets.cpp ../lab1/include/brackets.h)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)

add_test(lab1_test lab1_test)


add_executable(lab1_test+ lab1_tests+.cpp ../lab1/src/brackets.cpp ../lab1/include/brackets.h)

target_link_libraries(lab1_test+ PRIVATE GTest::GTest)
target_include_directories(lab1_test+ PRIVATE ../lab1/include)

add_test(lab1_test+ lab1_test+)



add_executable(test_lab2 test_lab2.cpp ../lab2/scr/array.cpp ../lab2/include/array.h ../lab2/scr/seven.cpp ../lab2/include/seven.h)

target_link_libraries(test_lab2 PRIVATE GTest::GTest)
target_include_directories(test_lab2 PRIVATE ../lab2/include)

add_test(test_lab2 test_lab2)


add_executable(test+_lab2 test+_lab2.cpp ../lab2/scr/array.cpp ../lab2/include/array.h ../lab2/scr/seven.cpp ../lab2/include/seven.h)

target_link_libraries(test+_lab2 PRIVATE GTest::GTest)
target_include_directories(test+_lab2 PRIVATE ../lab2/include)

add_test(test+_lab2 test_lab2)


