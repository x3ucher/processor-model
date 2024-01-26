cmake_minimum_required(VERSION 3.16)
project(instr)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исходные файлы
set(SOURCE_FILES
    #source/commands.cpp
    #source/instructions.cpp
    source/operands.cpp

    include/operands.hpp
    #include/instructions.hpp
    #include/commands.hpp
)

# Создаем библиотеку с именем instr
add_library(instr STATIC ${SOURCE_FILES})

set_target_properties(instr PROPERTIES LINKER_LANGUAGE CXX)

# Указываем, что этот подпроект будет доступен другим подпроектам
target_include_directories(instr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../utils ../cpu ) 
