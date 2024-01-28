
cmake_minimum_required(VERSION 3.16)
project(dialogue)

set(CMAKE_CXX_STANDARD 20)

add_executable(dialogue dialogue.cpp)
target_link_libraries(dialogue asm cpu instr utils)