cmake_minimum_required(VERSION 3.0)

project(Curves)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(Curves)

add_executable(exe main.cpp)

target_link_libraries(exe PUBLIC curves)
