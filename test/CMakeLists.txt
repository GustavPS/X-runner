cmake_minimum_required(VERSION 3.6)
project(SFML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

set(SOURCE_FILES main.cpp classes/Player.cc classes/Platform.cc classes/Block.cc classes/Collision.cc)
add_executable(SFML ${SOURCE_FILES})
target_link_libraries(SFML sfml-graphics sfml-window sfml-system)