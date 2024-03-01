# самый главный 
cmake_minimum_required(VERSION 3.16)

#
project(processor)

#
set(CMAKE_CXX_STANDARD 20)

#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

# add_compile_options(--coverage)
# add_link_options(--coverage)

# добавление подпроекта с библиотекой
add_subdirectory(utils)
add_subdirectory(myvector)
add_subdirectory(asm)
add_subdirectory(cpu)
add_subdirectory(instructions)
add_subdirectory(tests)

add_subdirectory(dialogue)

# gcovr -r .. -e CMakeFiles --html-details -o coverage.html .