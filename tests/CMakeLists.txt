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

add_executable(lab7_test
        lab7_tests_basic.cpp
        ../lab7/src/bear.cpp
        ../lab7/src/elf.cpp
        ../lab7/src/factory.cpp
        ../lab7/src/game_basic.cpp
        ../lab7/src/npc.cpp
        ../lab7/src/observer.cpp
        ../lab7/src/robber.cpp
        ../lab7/src/visitor.cpp
)
target_link_libraries(lab7_test PRIVATE GTest::GTest)
target_include_directories(lab7_test PRIVATE ../lab7/include)
add_test(lab7_test lab7_test)

