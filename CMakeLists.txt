cmake_minimum_required(VERSION 3.10)
project(EcosystemSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(
    include
    include/core
    include/graphics
    include/utils
    include/world
    include/world/elements
    include/world/biomes
    include/world/generation
)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(EcosystemSimulation ${SOURCES})
target_link_libraries(EcosystemSimulation sfml-graphics sfml-window sfml-system)