cmake_minimum_required(VERSION 3.20)

project(InteractivePhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2 COMPONENTS
    graphics
    window
    system
    REQUIRED
)

add_executable(PhysicsEngine
    src/main.cpp
)

target_link_libraries(PhysicsEngine PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)