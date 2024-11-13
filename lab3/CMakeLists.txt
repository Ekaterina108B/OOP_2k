add_executable(OOP_3 include/figure.h include/rectangle.h include/trapezoid.h include/rhombus.h src/rectangle.cpp src/trapezoid.cpp src/rhombus.cpp include/array.h main.cpp)

target_include_directories(OOP_3 PRIVATE include)