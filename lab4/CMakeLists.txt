add_executable(OOP_4 include/figure.h include/rectangle.h include/trapezoid.h include/rhombus.h include/point.h include/array.h main.cpp)

target_include_directories(OOP_4 PRIVATE include)

target_compile_features(OOP_4 PRIVATE cxx_std_20)