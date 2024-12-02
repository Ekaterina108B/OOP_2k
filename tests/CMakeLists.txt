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

add_executable(lab6_test lab6_test.cpp ../lab6/src/bear.cpp ../lab6/src/elf.cpp ../lab6/src/factory.cpp ../lab6/src/game.cpp ../lab6/src/npc.cpp ../lab6/src/observer.cpp ../lab6/src/robber.cpp ../lab6/src/visitor.cpp)
target_link_libraries(lab6_test PRIVATE GTest::GTest)
target_include_directories(lab6_test PRIVATE ../lab6/include)
add_test(lab6_test lab6_test)


add_executable(lab6_test+ lab6_test+.cpp ../lab6/src/bear.cpp ../lab6/src/elf.cpp ../lab6/src/factory.cpp ../lab6/src/game.cpp ../lab6/src/npc.cpp ../lab6/src/observer.cpp ../lab6/src/robber.cpp ../lab6/src/visitor.cpp)
target_link_libraries(lab6_test+ PRIVATE GTest::GTest)
target_include_directories(lab6_test+ PRIVATE ../lab6/include)
add_test(lab6_test+ lab6_test+)


