cmake_minimum_required(VERSION 3.20)

project(OOP_LABS)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lab7)

add_subdirectory(tests)