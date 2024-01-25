cmake_minimum_required(VERSION 3.16)
project(cpu)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исходные файлы
set(SOURCE_FILES
    source/memory.cpp
    # source/processor.cpp
    source/registers.cpp
    # source/thread.cpp

    include/memory.hpp
    # include/processor.hpp
    include/registers.hpp
    # include/thread.hpp
)

# Создаем библиотеку с именем utils
add_library(cpu STATIC ${SOURCE_FILES})

set_target_properties(cpu PROPERTIES LINKER_LANGUAGE CXX)

# Указываем, что этот подпроект будет доступен другим подпроектам
target_include_directories(cpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../utils ../instr ../asm) 
