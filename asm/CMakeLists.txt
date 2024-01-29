cmake_minimum_required(VERSION 3.16)
project(asm)

set(CMAKE_CXX_STANDARD 20)

# add_library(utils INTERFACE)
# target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем исходные файлы
set(SOURCE_FILES
    source/assemble.cpp
    source/cleaner_base.cpp
    source/cleaner_thread.cpp

    include/assembler.hpp
)

# Создаем библиотеку с именем utils
add_library(asm STATIC ${SOURCE_FILES})

set_target_properties(asm PROPERTIES LINKER_LANGUAGE CXX)

# Указываем, что этот подпроект будет доступен другим подпроектам
target_include_directories(asm PUBLIC ../utils ../instructions ../cpu) 

target_include_directories(asm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
