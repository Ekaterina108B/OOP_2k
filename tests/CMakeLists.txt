include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 20)

add_executable(lab5_test lab5_test.cpp ../lab5/src/memory_resource.cpp)

target_link_libraries(lab5_test PRIVATE GTest::GTest)
target_include_directories(lab5_test PRIVATE ../lab5/include)

add_test(lab5_test lab5_test)


add_executable(lab5_test+ lab5_test+.cpp ../lab5/src/memory_resource.cpp)

target_link_libraries(lab5_test+ PRIVATE GTest::GTest)
target_include_directories(lab5_test+ PRIVATE ../lab5/include)

add_test(lab5_test+ lab5_test+)


