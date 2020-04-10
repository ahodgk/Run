cmake_minimum_required(VERSION 3.15)
project(Run)

set(CMAKE_CXX_STANDARD 14)

add_executable(Run main.cpp Game.cpp Game.h Player.cpp Player.h Obstacle.cpp Obstacle.h)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
# Detect and add SFML
set(SFML_ROOT "C:/C++ Libs/SFML-2.5.1")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED audio network graphics window system)
target_link_libraries(Run sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
