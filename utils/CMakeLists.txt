cmake_minimum_required(VERSION 3.16)
project(utils)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исходные файлы
set(SOURCE_FILES
    source/binarycode.cpp

    include/binarycode.hpp
    include/configconst.hpp
)

# Создаем библиотеку с именем utils
add_library(utils STATIC ${SOURCE_FILES})

set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)

# Указываем, что этот подпроект будет доступен другим подпроектам
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
