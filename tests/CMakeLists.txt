cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_STANDARD 20)

# Путь к библиотеке Catch2 (из vcpkg)
#set(Catch2_DIR /home/urtoach/vcpkg/installed/x64-linux/share/catch2)

find_package(Catch2 REQUIRED)

# Добавляем исполняемый файл для тестов myvector
add_executable(myvector_tests myvector_testing.cpp)
target_link_libraries(myvector_tests myvector Catch2::Catch2)

# Добавляем исполняемый файл для тестов binarycode
add_executable(utils_tests utils_testing.cpp)
target_link_libraries(utils_tests utils Catch2::Catch2)

# Добавляем исполняемый файл для тестов asm
add_executable(asm_tests asm_testing.cpp)
target_link_libraries(asm_tests asm Catch2::Catch2)

# Добавляем исполняемый файл для тестов registers
add_executable(registers_tests registers_testing.cpp)
target_link_libraries(registers_tests cpu Catch2::Catch2)

# Добавляем исполняемый файл для тестов memory
add_executable(memory_tests memory_testing.cpp)
target_link_libraries(memory_tests utils cpu Catch2::Catch2)

# Добавляем исполняемый файл для тестов proc
add_executable(cpu_tests cpu_testing.cpp)
target_link_libraries(cpu_tests cpu utils asm Catch2::Catch2)

# Добавляем исполняемый файл для тестов operands
add_executable(operands_tests operands_testing.cpp)
target_link_libraries(operands_tests instr utils cpu asm Catch2::Catch2)

# Добавляем исполняемый файл для тестов commands
add_executable(commands_tests commands_testing.cpp)
target_link_libraries(commands_tests instr utils cpu asm Catch2::Catch2)