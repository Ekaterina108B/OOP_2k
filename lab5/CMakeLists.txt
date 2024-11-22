add_executable(OOP_5 src/memory_resource.cpp main.cpp)

target_include_directories(OOP_5 PRIVATE include)

target_compile_features(OOP_5 PRIVATE cxx_std_20)