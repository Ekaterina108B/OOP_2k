set(COMMON_SOURCES
    src/bear.cpp
    src/elf.cpp
    src/factory.cpp
    src/npc.cpp
    src/observer.cpp
    src/robber.cpp
    src/visitor.cpp
)

set(COROUTINE_SOURCES
    src/game.cpp
    main.cpp
)

add_executable(OOP7_corutine
    ${COMMON_SOURCES}
    ${COROUTINE_SOURCES}
)
target_include_directories(OOP7_corutine PRIVATE include)
target_compile_features(OOP7_corutine PRIVATE cxx_std_20)