add_executable(OOP_6 src/bear.cpp src/elf.cpp src/factory.cpp src/game.cpp src/npc.cpp src/observer.cpp src/robber.cpp src/visitor.cpp main.cpp)

target_include_directories(OOP_6 PRIVATE include)

target_compile_features(OOP_6 PRIVATE cxx_std_20)