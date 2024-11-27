add_executable(OOP_6 src/bear.cpp src/elf.cpp src/factore.cpp src/game.cpp src/npc.cpp src/obserser.cpp src/robber.cpp src/visitor.cpp src/main.cpp)

target_include_directories(OOP_6 PRIVATE include)

target_compile_features(OOP_6 PRIVATE cxx_std_20)